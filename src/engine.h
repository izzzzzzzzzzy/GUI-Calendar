#ifndef GRAPHICS_ENGINE_H
#define GRAPHICS_ENGINE_H

#include <vector>
#include <memory>
#include <GLFW/glfw3.h>
#include <time.h>

#include "font/fontRenderer.h"
#include "shader/shaderManager.h"
#include "shapes/datebox.h"
#include "Date.h"
#include "Month.h"
#include "DayOfWeek.h"

using std::vector, std::unique_ptr, std::make_unique, glm::ortho, glm::mat4, glm::vec3, glm::vec4;

/**
 * @brief The Engine class.
 * @details The Engine class is responsible for initializing the GLFW window, loading shaders, and rendering the game state.
 */
class Engine
{
private:
    /// @brief The actual GLFW window.
    GLFWwindow *window{};

    /// @brief The width and height of the window.
    const float width = 800, height = 800; // Window dimensions
    /// @brief The projection matrix
    const glm::mat4 projection = glm::ortho(0.0f, (float)width, 0.0f, (float)height);

    /// @brief Keyboard state (True if pressed, false if not pressed).
    /// @details Index this array with GLFW_KEY_{key} to get the state of a key.
    bool keys[1024];

    /// @brief Responsible for loading and storing all the shaders used in the project.
    /// @details Initialized in initShaders()
    unique_ptr<ShaderManager> shaderManager;

    /// @brief Responsible for rendering text on the screen.
    /// @details Initialized in initShaders()
    unique_ptr<FontRenderer> fontRenderer;

    Shader shapeShader;
    Shader textShader;

    vector<unique_ptr<DateBox>> grid = vector<unique_ptr<DateBox>>(42);
    Date today;

    unique_ptr<Rect> leftYearButton, rightYearButton, leftMonthButton, rightMonthButton;

    double MouseX, MouseY;
    bool mousePressedLastFrame;

    vector<int> dayInMonthCount = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    vector<Month> theYear = {Month::January, Month::February, Month::March, Month::April, Month::May, Month::June, Month::July, Month::August, Month::September, Month::October, Month::November, Month::December};
    vector<string> theWeek = {"Sun", "Mon", "Tues", "Wed", "Thurs", "Fri", "Sat"};

public:
    /// @brief Constructor for the Engine class.
    /// @details Initializes window and shaders.
    Engine();

    /// @brief Destructor for the Engine class.
    ~Engine();

    /// @brief Initializes the GLFW window.
    /// @return 0 if successful, -1 otherwise.
    unsigned int initWindow(bool debug = false);

    /// @brief Loads shaders from files and stores them in the shaderManager.
    /// @details Renderers are initialized here.
    void initShaders();

    /// @brief Initializes the shapes to be rendered.
    void initShapes();

    /// @brief Processes input from the user.
    /// @details (e.g. keyboard input, mouse input, etc.)
    void processInput();

    /// @brief Updates the game state.
    /// @details (e.g. collision detection, delta time, etc.)
    void update();

    /// @brief Renders the game state.
    /// @details Displays/renders objects on the screen.
    void render();

    void setGrid();

    /* deltaTime variables */
    float deltaTime = 0.0f; // Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame (used to calculate deltaTime)

    /// @brief Returns true if the window should close.
    /// @details (Wrapper for glfwWindowShouldClose()).
    /// @return true if the window should close
    /// @return false if the window should not close
    bool shouldClose();

    /// Projection matrix used for 2D rendering (orthographic projection).
    /// We don't have to change this matrix since the screen size never changes.
    /// OpenGL uses the projection matrix to map the 3D scene to a 2D viewport.
    /// The projection matrix transforms coordinates in the camera space into normalized device coordinates (view space to clip space).

    /// @note The projection matrix is used in the vertex shader.
    // 4th quadrant
    const mat4 PROJECTION = ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), -1.0f, 1.0f);
    // 1st quadrant
    //        mat4 PROJECTION = ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));

    /// @brief Debug function to check for OpenGL errors.
    GLenum glCheckError_(const char *file, int line);
/// @brief Macro for glCheckError_ function. Used for debugging.
#define glCheckError() glCheckError_(__FILE__, __LINE__)
};

#endif // GRAPHICS_ENGINE_H