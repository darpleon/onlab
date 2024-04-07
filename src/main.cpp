// #include "glad.h"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <vector>

#include <iostream>
#include <format>
#include <algorithm>
#include <complex>

#include "Context.hpp"
#include "Graphics.hpp"
#include "PHDemo.hpp"
#include "Polynomial.hpp"
#include "PHPlanarQuintic.hpp"
#include "Listener.hpp"

using namespace std::complex_literals;
using complex = std::complex<float>;

int main()
{
    GLFWwindow* window = Context::init();

    Graphics::init();

    Graphics::draw();
    glfwSwapBuffers(window);
    // Polynomial<glm::vec2> p{{0.4f, -0.2f}, {4.0f, 0.2f}, {-9.4f, 5.2f}, {5.2f, -5.2f}};
    // Bernstein<complex> b{-0.8f + 0.5if, -0.4f - 0.3if, 0.6f + 0.7if, 0.7f - 0.6if};
    Bernstein<glm::vec2> b{{-0.8f, 0.5}, {0.0f, 0.0f}, {0.6f, 0.7f}, {0.7f, -0.6f}};
    Graphics::BernsteinView bv{&b};
    // Graphics::add_object(&bv);
    std::array<glm::vec2, 4> ctr{{{-0.8f, 0.5f}, {0.0f, 0.0f}, {0.6f, 0.7f}, {0.7f, -0.6f}}};
    PHDemo phd{ctr};
    Context::add_listener(&phd);
    // PHPlanarQuintic ph{ctr};
    // Graphics::PHPlanarQuinticView phv{&ph};
    // Graphics::add_object(&phv);
    // Graphics::PolynomialView pv{&p};
    // Graphics::add_object(&pv);
    while (!glfwWindowShouldClose(window))
    {
        Context::processInput(window);

        Graphics::draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
        Context::rotate(0.01f);
        Context::update();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    // glDeleteVertexArrays(1, &clineVAO);
    // glDeleteBuffers(1, &clineVBO);
    // glDeleteProgram(shaderProgramOrange);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

