#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>

////////////////////////////////////////////////////////////////
#define RED(X)   ((X)%256)
#define GREEN(X) ((X)/256)%256
#define BLUE(X)  ((X)/65536)%256
#define EXIT_IF(X, ...) do {         \
    if(X) {                          \
      fprintf(stderr, __VA_ARGS__);  \
      return EXIT_FAILURE;           \
    }                                \
  } while (0)
#define USAGE_STR "Usage: %s  [-f delay] [-w width] [-hmM]\n\n\t-f delay\t Specify delay between frames (e.g '-f 10')\n\t-h\t\t Display this help message\n\t-m\t\t Enables the keyboard to control frames at the end of the run\n\t-M\t\t Enables the keyboard to control frames at the start of the run\n\t-w width\t Specify the width of the SDL window (e.g '-w 100')\n"

static unsigned int window_width = 640;
static unsigned int frame_speed = 50;

// Boolean globals
static unsigned int manual_control = 0;
static unsigned int wait_at_end = 0;

////////////////////////////////////////////////////////////////
static void parse_opts(int argc, char* argv[]) {
  int opt;
  while ((opt = getopt(argc, argv, "hmMf:w:")) != -1) {
    switch(opt) {
      case 'f': // Frame speed
        frame_speed = atoi(optarg);
        if (frame_speed == 0) frame_speed = 1;
        break;
      case 'h': // Display usage
        printf(USAGE_STR, argv[0]);
        exit(EXIT_SUCCESS);
        break;
      case 'm': // Manual control at end
        wait_at_end = 1;
        break;
      case 'M': // Manual control at start
        wait_at_end = 1;
	manual_control = 1;
        break;
      case 'w': // Window width
        window_width = atoi(optarg);
        if (window_width == 0) window_width = 1;
        break;
      default:
        fprintf(stderr, USAGE_STR, argv[0]);
        exit(EXIT_FAILURE);
    }
  }
}

static void print_manual_control_help() {
  fprintf(stderr, "To control the display, focus the SDL window and:\n");
  fprintf(stderr, "\t* press the right arrow key to show the next frame\n");
  fprintf(stderr, "\t* press the left arrow key to show the previous frame\n");
  fprintf(stderr, "\t* press the 'q' key to quit\n");
}

////////////////////////////////////////////////////////////////
// Data type for images
struct world {
  unsigned int w;
  unsigned int h;
  unsigned int** frames;
  unsigned int nb_frames;
  unsigned int nb_allocated_frames;
};

static struct world* alloc_world(unsigned int w, unsigned int h) {
  struct world* wld = malloc(sizeof (struct world));
  wld->w = w;
  wld->h = h;
  wld->nb_frames = 0;
  wld->nb_allocated_frames = 5;
  wld->frames = malloc(wld->nb_allocated_frames*sizeof(unsigned int*));
  return wld;
}

static void free_world(struct world* w) {
  for (unsigned int i = 0; i < w->nb_frames; i++) {
    free(w->frames[i]);
  }
  free(w->frames);
  free(w);
}

////////////////////////////////////////////////////////////////
// SDL helper for drawing a colored rectangle
static inline void draw_rect(SDL_Renderer* renderer,
                             int x, int y, int w, int h,
                             unsigned int c) {
  SDL_Rect r = { .x=x, .y=y, .w=w, .h=h };
  SDL_SetRenderDrawColor(renderer, RED(c), GREEN(c), BLUE(c), 0);
  SDL_RenderFillRect(renderer, &r);
}

static int read_frame(struct world* wld) {
  if (scanf("#\n") == EOF) {
    return 0;
  }

  wld->nb_frames++;
  if (wld->nb_frames > wld->nb_allocated_frames) {
    wld->nb_allocated_frames *= 2;
    wld->frames = realloc(wld->frames, wld->nb_allocated_frames*sizeof(unsigned int*));
  }
  wld->frames[wld->nb_frames-1] = malloc(wld->w*wld->h*sizeof(unsigned int));

  for(unsigned int i = 0; i < wld->h; i++) {
    for(unsigned int j = 0; j < wld->w; j++) {
      unsigned int val;
      /* scanf doesn't distinguish between spaces and new lines, and returns
       * the number of read patterns, so it's not easy to check if all cells
       * are correctly present... */
      int nb_items_read = scanf("%d ", &val);
      if (nb_items_read == EOF) {
          goto error;
      }
      else if (nb_items_read != 1) {
        printf("Error while reading cell value\n");
        goto error;
      }
      wld->frames[wld->nb_frames-1][j+i*wld->w] = val;
    }
  }
  return 1;
error:
  free(wld->frames[wld->nb_frames-1]);
  wld->nb_frames--;
  return 0;
}

static void read_frames(struct world* wld)
{
  int ret;
  do {
    ret = read_frame(wld);
  } while (ret);
}

////////////////////////////////////////////////////////////////
// Display an image with rectangles
// size is the size of the rectangles
static void disp_frame(SDL_Renderer* renderer, unsigned int size,
                       const struct world* wld, unsigned int frame_id,
                       int quiet) {
  if (!quiet) printf("Displaying frame #%u\n", frame_id);
  SDL_RenderClear(renderer);
  for(unsigned int i = 0; i<wld->w; i++)
    for(unsigned int j = 0; j<wld->h; j++)
      draw_rect(renderer, i*size, j*size, size, size,
                wld->frames[frame_id][i+j*(wld->w)]);
  SDL_RenderPresent(renderer);
}

////////////////////////////////////////////////////////////////
// Wait for next event
//
// Always returns true if control is automatic, otherwise returns true
// only if an event has been raised.
static inline int wait_next_event(SDL_Event* event) {
  if (manual_control) {
    // Explicitely wait on events to reduce CPU load:
    return SDL_WaitEvent(event);
  }
  else {
    /* When the manual control is disabled, we don't want the event
     * loop to be blocked by this function, so we use the
     * SDL_PollEvent: */
    SDL_PollEvent(event);

    /* SDL_PollEvent can return 0 if no event is pending, but we
     * always want to return 1 to avoid stopping the event loop: */
    return 1;
  }
}

static void sdl_loop(SDL_Renderer* renderer, const struct world* wld,
                     unsigned int pixel_size) {
  int is_running = 1;
  unsigned int current_frame_id = 0;
  SDL_Event event;

  // display the first frame:
  disp_frame(renderer, pixel_size, wld, current_frame_id, 0);

  // start the event loop:
  while (is_running && wait_next_event(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        is_running = 0;
        break;
      case SDL_WINDOWEVENT:
        if ((event.window.event == SDL_WINDOWEVENT_TAKE_FOCUS) ||
            (event.window.event == SDL_WINDOWEVENT_EXPOSED))
          disp_frame(renderer, pixel_size, wld, current_frame_id, 1);
        break;
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_q ||
            event.key.keysym.sym == SDLK_ESCAPE) {
          is_running = 0;
	} else if (manual_control) {
          if (event.key.keysym.sym == SDLK_l ||
              event.key.keysym.sym == SDLK_RIGHT ||
              event.key.keysym.sym == SDLK_n) {
            if (current_frame_id+1 < wld->nb_frames) {
              current_frame_id++;
              disp_frame(renderer, pixel_size, wld, current_frame_id, 0);
            }
            else {
              fprintf(stderr, "There is no other frame to display.\n");
            }
          }
          else if (event.key.keysym.sym == SDLK_h ||
                   event.key.keysym.sym == SDLK_LEFT ||
                   event.key.keysym.sym == SDLK_p) {
            if (current_frame_id != 0) {
              current_frame_id--;
              disp_frame(renderer, pixel_size, wld, current_frame_id, 0);
            }
            else {
              fprintf(stderr, "There is no negative frame to display.\n");
            }
          }
        }
        break;
    }

    if (!manual_control) {
        if (current_frame_id+1 < wld->nb_frames) {
          SDL_Delay(frame_speed);
          current_frame_id++;
          disp_frame(renderer, pixel_size, wld, current_frame_id, 0);
        }
        else if (wait_at_end) {
          manual_control = 1;
          fprintf(stderr, "There is no other frame to display, "
                  "switching to manual mode.\n");
          print_manual_control_help();
        } else
	  return;
    }
  }
}

////////////////////////////////////////////////////////////////
int main(int argc, char *argv[]) {
  unsigned int width, height, pixel_size;
  parse_opts(argc, argv);

  if (isatty(fileno(stdin))) {
    fprintf(stderr, "Error: redirect the sandwich output "
            "to this program to display it. For instance:\n");
    fprintf(stderr, "\t./project | %s\n", argv[0]);
    return EXIT_FAILURE;
  }

  fscanf(stdin, "%d %d\n", &width, &height);
  EXIT_IF((width > window_width) || (height > window_width),
          "Dimensions too large: Width=%u Height=%u whereas Window_width=%u\n",
	  width, height, window_width);
  printf("World sizes: Width=%u Height=%u\n", width, height);
  pixel_size = window_width / width;

  if (manual_control) {
    fprintf(stderr, "Manual mode is enabled.\n");
    print_manual_control_help();
  }

  struct world* wld = alloc_world(width, height);
  read_frames(wld);

  EXIT_IF(SDL_Init(SDL_INIT_VIDEO) != 0,
          "Could not init SDL: %s\n", SDL_GetError());
  SDL_Window *screen = SDL_CreateWindow("Sandwich",
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        window_width,
                                        window_width*height/width,
                                        0);
  EXIT_IF(!screen, "Could not create SDL window\n");

  SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1,
                                              SDL_RENDERER_SOFTWARE);
  EXIT_IF(!renderer, "Could not create SDL renderer\n");

  sdl_loop(renderer, wld, pixel_size);

  free_world(wld);

  SDL_DestroyWindow(screen);
  SDL_Quit();
  return EXIT_SUCCESS;
}
