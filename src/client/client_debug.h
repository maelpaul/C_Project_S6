// Returns the current id of the client
size_t id_debug(void);

// Returns the current graph (client-side)
struct graph_t* graph_debug(void);

// Returns the current color array (client-side)
enum color_t* colors_debug(void);

// Returns the current forbidden colors (client-side)
struct color_set_t* forbidden_debug(void);

// Updates the current_graph and current_colors
void update_map(struct move_t* move, size_t id);

int bfs_counter(size_t id,struct graph_t* graph, enum color_t* colors);

int fake_game(enum color_t color, int plays);

void fake_update_map(struct move_t* move, size_t id, struct graph_t* graph, enum color_t* colors);