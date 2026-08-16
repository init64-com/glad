
#include <glext/gl.h>
#include <GLFW/glfw3.h>

void create_triangle(void);
void render_triangle(void);
void destroy_triangle(void);

void refresh_callback(GLFWwindow *window) {}

int main() {
  if (!glfwInit()) {
    return 1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLFWwindow *window = glfwCreateWindow(800, 600, "GL Window", NULL, NULL);
  glfwMakeContextCurrent(window);

  if (!window) {
    return 1;
  }

  glfwSetWindowSizeLimits(window, 600, 400, GLFW_DONT_CARE, GLFW_DONT_CARE);

  if (!glext_LoaderLoadGL()) {
    return 1;
  }
  glfwSetWindowRefreshCallback(window, refresh_callback);

  create_triangle();

  while (!glfwWindowShouldClose(window)) {
    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    render_triangle();
    glfwSwapBuffers(window);

    glfwWaitEvents();
  }

  glext_LoaderUnloadGL();
  if (window) {
    glfwDestroyWindow(window);
  }
  glfwTerminate();
}

// todo: make this less ugly. It hurts when I read this.
// It's obvious what I'm trying to say.

GLuint vao, vbo, program;
const char *vertex_shader_source =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragment_shader_source =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

void create_triangle() {
  GLfloat data[] = {
      1.0f, 1.0f, 0.0f, -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f,
  };

  glCreateVertexArrays(1, &vao);
  glCreateBuffers(1, &vbo);

  glNamedBufferStorage(vbo, sizeof(data), data, 0);

  glVertexArrayVertexBuffer(vao, 0, vbo, 0, 3 * sizeof(GLfloat));
  glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
  glVertexArrayAttribBinding(vao, 0, 0);
  glEnableVertexArrayAttrib(vao, 0);

  program = glCreateProgram();
  GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
  glCompileShader(vertex_shader);

  GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
  glCompileShader(fragment_shader);

  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);

  glLinkProgram(program);
}

void render_triangle() {
  glBindVertexArray(vao);
  glUseProgram(program);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

