# Graphics Editor Documentation

## Core Functions

### Drawing Algorithms (`algorithms.h`)

#### `void drawCircle(const Vector2 *center, int radius, const Color *c, drawPixel_func draw_pixel, void *ctx)`
- Draws a circle using Midpoint Circle Algorithm
- Parameters:
  - `center`: Pointer to circle center coordinates (Vector2)
  - `radius`: Circle radius in pixels
  - `c`: Pointer to Color structure
  - `draw_pixel`: Function pointer for pixel drawing
  - `ctx`: Context pointer for pixel buffer

#### `void drawLine(const Vector2 *point, const Vector2 *point2, const Color *c, int line_width, int isDotted, drawPixel_func draw_pixel, void *ctx)`
- Draws a line between two points
- Parameters:
  - `point`, `point2`: Start/end points (Vector2)
  - `c`: Line color (Color)
  - `line_width`: Thickness in pixels
  - `isDotted`: 1 for dotted line, 0 for solid
  - `draw_pixel`: Pixel drawing function
  - `ctx`: Pixel buffer context

#### `void drawPolygon(const Vector2 *points, size_t count, const Color *c, drawPixel_func drawPixel, void *ctx)`
- Draws a polygon from point array
- Parameters:
  - `points`: Array of vertices (Vector2)
  - `count`: Number of vertices
  - `c`: Polygon color
  - `drawPixel`: Drawing function
  - `ctx`: Context pointer

#### `void drawSquare(const Vector2 *start, const Vector2 *end, const Color *c, drawPixel_func drawPixel, void *ctx)`
- Draws axis-aligned square
- Parameters:
  - `start`: First corner point
  - `end`: Opposite corner point
  - `c`: Square color
  - `drawPixel`: Drawing function
  - `ctx`: Context pointer

### Button System (`button.h`)

#### `Button *button_create(int posX, int posY, char *sprite_src, char *name)`
- Creates a new button
- Parameters:
  - `posX`, `posY`: Screen position
  - `sprite_src`: Texture file path
  - `name`: Button identifier
- Returns: Pointer to new Button

#### `int button_is_clicked(Button *button)`
- Checks if button was clicked
- Parameters:
  - `button`: Button to check
- Returns: 1 if clicked, 0 otherwise

#### `void button_draw(Button *button)`
- Renders a button
- Parameters:
  - `button`: Button to draw

#### `void button_destroy(Button *button)`
- Frees button resources
- Parameters:
  - `button`: Button to destroy

### Pixel Buffer (`pixelBuffer.h`)

#### `void pixelBuffer_setPixel(int x, int y, Color c, void *ctx)`
- Sets pixel color in buffer
- Parameters:
  - `x`, `y`: Coordinates
  - `c`: Color to set
  - `ctx`: Pixel buffer context

#### `pixelBuffer *pixelBuffer_create()`
- Creates new pixel buffer
- Returns: Initialized pixel buffer

#### `void pixelBuffer_clear(pixelBuffer *buffer)`
- Clears the buffer to transparent
- Parameters:
  - `buffer`: Target buffer

### Input Handlers (`handlers.h`)

#### `void line_mouse_handler(int mouseButton, int mouseEvent, pixelBuffer *buffer, EditorData *editordata)`
- Handles line tool mouse input
- Parameters:
  - `mouseButton`: Which button (MOUSE_LEFT/RIGHT)
  - `mouseEvent`: PRESS/RELEASE/DRAG/IDLE
  - `buffer`: Target pixel buffer
  - `editordata`: Current editor state

#### `void circle_key_handler(int key, pixelBuffer *buffer, EditorData *editordata)`
- Handles circle tool keyboard input
- Parameters:
  - `key`: Pressed key code
  - `buffer`: Target buffer
  - `editordata`: Editor state

#### `void fill(int startX, int startY, pixelBuffer *buffer, EditorData *editordata)`
- Flood fill implementation
- Parameters:
  - `startX`, `startY`: Fill origin
  - `buffer`: Target buffer
  - `editordata`: Editor state

### UI System (`handle-ui.h`)

#### `void handle_ui_init()`
- Initializes all UI buttons

#### `void handle_ui(EditorData *editordata)`
- Main UI rendering/handling
- Parameters:
  - `editordata`: Current editor state

#### `void handle_ui_destroy()`
- Cleans up UI resources

## Utility Functions

#### `Vector2 snapTo(Vector2 p1, Vector2 p2)`
- Snaps vector to nearest 45° angle
- Parameters:
  - `p1`: Origin point
  - `p2`: Target point
- Returns: Snapped coordinates

#### `float getVectorDistance(Vector2 p1, Vector2 p2)`
- Calculates distance between points
- Parameters:
  - `p1`, `p2`: Points to measure
- Returns: Distance in pixels

#### `int isPointValid(Vector2 point)`
- Checks if point is within canvas
- Parameters:
  - `point`: Coordinate to check
- Returns: 1 if valid, 0 otherwise
