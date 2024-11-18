#include "engine.h"

const color dateOn(0.8f, 0.8f, 0.8f);
const color dateOnHover(0.9f, 0.9f, 0.9f);
const color dateOff(0.4f, 0.4f, 0.4f);
const color dateOffHover(0.5f, 0.5f, 0.5f);
const color dateCurrent(0.8f, 0.8f, 0.0f);
const color dateCurrentHover(0.9f, 0.9f, 0.0f);
const color button(0.6f, 0.6f, 0.6f);
const color buttonHover(0.7f, 0.7f, 0.7f);

using namespace std;

Engine::Engine() : keys()
{
    this->initWindow();
    this->initShaders();
    this->initShapes();
}

Engine::~Engine() {}

unsigned int Engine::initWindow(bool debug)
{
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, false);

    window = glfwCreateWindow(width, height, "engine", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    // OpenGL configuration
    glViewport(0, 0, width, height);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glfwSwapInterval(1);

    return 0;
}

void Engine::initShaders()
{
    // load shader manager
    shaderManager = make_unique<ShaderManager>();

    // Load shader into shader manager and retrieve it
    shapeShader = this->shaderManager->loadShader("../res/shaders/shape.vert", "../res/shaders/shape.frag", nullptr, "shape");

    // Configure text shader and renderer
    textShader = shaderManager->loadShader("../res/shaders/text.vert", "../res/shaders/text.frag", nullptr, "text");
    fontRenderer = make_unique<FontRenderer>(shaderManager->getShader("text"), "../res/fonts/MxPlus_IBM_BIOS.ttf", 24);

    // Set uniforms
    textShader.setVector2f("vertex", vec4(100, 100, .5, .5));
    shapeShader.use();
    shapeShader.setMatrix4("projection", this->PROJECTION);
}

void Engine::initShapes()
{
    time_t time_ptr = time(NULL);
    struct tm* tm_local = localtime(&time_ptr);
    today = Date(tm_local->tm_mday, monthToString(static_cast<Month>(tm_local->tm_mon+1)), 1900 + tm_local->tm_year);

    setGrid();

    leftYearButton = make_unique<Rect>(shapeShader, vec2(50, height - 50), vec2(50, 50), button);
    rightYearButton = make_unique<Rect>(shapeShader, vec2(width - 50, height - 50), vec2(50, 50), button);
    leftMonthButton = make_unique<Rect>(shapeShader, vec2(125, height - 50), vec2(50, 50), button);
    rightMonthButton = make_unique<Rect>(shapeShader, vec2(width - 125, height - 50), vec2(50, 50), button);
}

void Engine::processInput()
{
    glfwPollEvents();

    // Set keys to true if pressed, false if released
    for (int key = 0; key < 1024; ++key)
    {
        if (glfwGetKey(window, key) == GLFW_PRESS)
            keys[key] = true;
        else if (glfwGetKey(window, key) == GLFW_RELEASE)
            keys[key] = false;
    }

    // Close window if escape key is pressed
    if (keys[GLFW_KEY_ESCAPE])
        glfwSetWindowShouldClose(window, true);

    // Mouse position saved to check for collisions
    glfwGetCursorPos(window, &MouseX, &MouseY);

    MouseY = height - MouseY; // make sure mouse y-axis isn't flipped

    bool mousePressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;

    if (leftYearButton->isOverlapping(vec2(MouseX, MouseY)))
    {
        leftYearButton->setColor(buttonHover);
        if (!mousePressed && mousePressedLastFrame)
        {
            today.decrementYear();
            setGrid();
        }
    }
    else
    {
        leftYearButton->setColor(button);
    }

    if (rightYearButton->isOverlapping(vec2(MouseX, MouseY)))
    {
        rightYearButton->setColor(buttonHover);
        if (!mousePressed && mousePressedLastFrame)
        {
            today.incrementYear();
            setGrid();
        }
    }
    else
    {
        rightYearButton->setColor(button);
    }

    if (leftMonthButton->isOverlapping(vec2(MouseX, MouseY))){
        leftMonthButton->setColor(buttonHover);
        if (!mousePressed && mousePressedLastFrame){
            today.decrementMonth();
            setGrid();
        }
    }
    else{
        leftMonthButton->setColor(button);
    }

    if (rightMonthButton->isOverlapping(vec2(MouseX, MouseY)))
    {
        rightMonthButton->setColor(buttonHover);
        if (!mousePressed && mousePressedLastFrame)
        {
            today.incrementMonth();
            setGrid();
        }
    }
    else
    {
        rightMonthButton->setColor(button);
    }

    for (unique_ptr<DateBox> &d : grid)
    {
        if (d->isOverlapping(vec2(MouseX, MouseY)))
        {
            if (today.equals(d->getDay()))
            {
                d->setColor(dateCurrentHover);
            }
            else if (today.getMonth() == d->getDay().getMonth())
            {
                d->setColor(dateOnHover);
            }
            else
            {
                d->setColor(dateOffHover);
            }

            if (!mousePressed && mousePressedLastFrame){
                today = d->getDay();
                setGrid();
            }
        }
        else
        {
            if (today.equals(d->getDay()))
            {
                d->setColor(dateCurrent);
            }
            else if (today.getMonth() == d->getDay().getMonth())
            {
                d->setColor(dateOn);
            }
            else
            {
                d->setColor(dateOff);
            }
        }
    }

    mousePressedLastFrame = mousePressed;
}

void Engine::update()
{
    // Calculate delta time
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

void Engine::render()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    vector<vec3> colors = {vec3{0,0,0},
                           vec3{173.0/255, 216.0/255, 230.0/255},//jan
                           vec3{255.0/255, 192.0/255, 203.0/255},//feb
                           vec3{80.0/255, 200.0/255, 120.0/255},//mar
                           vec3{255.0/255, 255.0/255, 204.0/255},//apr
                           vec3{255.0/255, 253.0/255, 208.0/255},//may
                           vec3{255.0/255, 179.0/255, 128.0/255},//jun
                           vec3{255.0/255, 255.0/255, 0.0/255},//jul
                           vec3{138.0/255, 54.0/255, 15.0/255},//aug
                           vec3{183.0/255, 65.0/255, 14.0/255},//sep
                           vec3{128.0/255, 0.0/255, 0.0/255},//oct
                           vec3{139.0/255, 69.0/255, 19.0/255},//nov
                           vec3{0.0/255, 0.0/255, 128.0/255}//dec


    };
    shapeShader.use();

    leftMonthButton->setUniforms();
    leftMonthButton->draw();
    rightMonthButton->setUniforms();
    rightMonthButton->draw();
    leftYearButton->setUniforms();
    leftYearButton->draw();
    rightYearButton->setUniforms();
    rightYearButton->draw();

    for (unique_ptr<DateBox> &d : grid)
    {
        d->setUniforms();
        d->draw();

        int x = d->getPosX(), y = d->getPosY();

        string num = to_string(d->getDay().getDay());
        fontRenderer->renderText(num, d->getRight() - 15 - (14 * num.length()), d->getTop() - 25, projection, 0.75f, vec3{0, 0, 0});

        shapeShader.use();
    }

    fontRenderer->renderText(monthToString(today.getMonth()), width / 2 - (18 * monthToString(today.getMonth()).length()), height - 50, projection, 1.5f, colors[static_cast<int>(today.getMonth())]);
    fontRenderer->renderText(to_string(today.getYear()), width / 2 - (12 * to_string(today.getYear()).length()), height - 75, projection, 1.0f, colors[static_cast<int>(today.getMonth())]);
    fontRenderer->renderText("<", 117, height - 60, projection, 1.0f, vec3{0, 0, 0});
    fontRenderer->renderText(">", width - 132, height - 60, projection, 1.0f, vec3{0, 0, 0});
    fontRenderer->renderText("-", 117, height - 60, projection, 1.0f, vec3{0, 0, 0});
    fontRenderer->renderText("-", width - 132, height - 60, projection, 1.0f, vec3{0, 0, 0});
    fontRenderer->renderText("<", 38, height - 60, projection, 1.0f, vec3{0, 0, 0});
    fontRenderer->renderText(">", width - 53, height - 60, projection, 1.0f, vec3{0, 0, 0});
    fontRenderer->renderText("<", 48, height - 60, projection, 1.0f, vec3{0, 0, 0});
    fontRenderer->renderText(">", width - 63, height - 60, projection, 1.0f, vec3{0, 0, 0});

    for (int i = 0; i < 7; i++){
        fontRenderer->renderText(theWeek[i], grid[i]->getPosX() - (9*theWeek[i].length()), grid[i]->getTop() + 10, projection, 0.75f, vec3{1, 1, 1});
    }

    glfwSwapBuffers(window);
}

void Engine::setGrid()
{
    DayOfWeek firstOfMonth = Date::firstDayFromMonthAndYear(today.getMonth(), today.getYear());

    int dayOfWeek = static_cast<int>(firstOfMonth) - 1;
    int daysInMonth = dayInMonthCount[static_cast<int>(today.getMonth()) - 1];
    int daysInPrevMonth = dayInMonthCount[today.getMonth() != Month::January ? (static_cast<int>(today.getMonth()) - 2) % 12 : 11];

    float offsetX = width / (4 * 7), sizeX = 3 * offsetX, edgeX = offsetX / 2;
    float offsetY = height / (4 * 7), sizeY = 3 * offsetY, edgeY = offsetY / 2;
    for (int i = 0; i < grid.size(); i++)
    {
        Date date((i - dayOfWeek) + 1, monthToString(today.getMonth()), today.getYear());

        if (date.getIsLeapYear() && date.getMonth() == Month::February)
        {
            daysInMonth = 29;
        }
        if (date.getIsLeapYear() && date.getMonth() == Month::March)
        {
            daysInPrevMonth = 29;
        }

        if (i < dayOfWeek)
        {
            date.decrementMonth();
            date.setDay(daysInPrevMonth - dayOfWeek + i + 1);
        }
        else if ((i - dayOfWeek) >= daysInMonth)
        {
            date.incrementMonth();
            date.setDay((i - dayOfWeek) - daysInMonth + 1);
        }
        grid[i] = make_unique<DateBox>(shapeShader, vec2((i % 7) * (offsetX + sizeX) + (edgeX + sizeX / 2), height - 100 - ((i / 7) * (offsetY + sizeY) + (edgeY + sizeY / 2))), vec2(sizeX, sizeY), date);
    }
}

bool Engine::shouldClose()
{
    return glfwWindowShouldClose(window);
}