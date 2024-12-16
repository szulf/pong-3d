#include "Game.hpp"
#include "GLFW/glfw3.h"
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "Window.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float2.hpp"
#include "glm/geometric.hpp"
#include "glm/trigonometric.hpp"
#include <optional>
#define GLM_ENABLE_EXPERIMENTAL false
#include "glm/gtx/string_cast.hpp"
#include <random>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

Game::Game(const std::string& title, int width, int height) : m_window{std::nullopt}
{
    if (!glfwInit())
    {
        throw std::runtime_error{"Error initializing glfw"};
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    m_window = std::optional{Window{title, width, height}};
    glfwMakeContextCurrent(m_window->get_window());

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        glfwTerminate();
        throw std::runtime_error{"Error settings GL Loader\n"};
    }

    // This sucks
    m_window->init_viewport();
}

auto Game::run() -> void
{
    // No idea why height is 0.2 but it works that way
    const auto rect_width = 0.2f;
    const auto rect_height = 0.2f;

    const auto cube_width = 0.2f;
    const auto cube_height = 0.2f;

    std::vector rect_vertices{
        -0.1f, -0.5f, 0.1f, 0.5f,
        -0.1f, 0.5f, 0.1f, 0.5f,
        0.1f, -0.5f, 0.1f, 0.5f,
        -0.1f, 0.5f, 0.1f, 0.5f,
        0.1f, -0.5f, 0.1f, 0.5f,
        0.1f, 0.5f, 0.1f, 0.5f,

        -0.1f, -0.5f, -0.1f, 0.5f,
        -0.1f, 0.5f, -0.1f, 0.5f,
        0.1f, -0.5f, -0.1f, 0.5f,
        -0.1f, 0.5f, -0.1f, 0.5f,
        0.1f, -0.5f, -0.1f, 0.5f,
        0.1f, 0.5f, -0.1f, 0.5f,

        -0.1f, 0.5f, -0.1f, 0.5f,
        -0.1f, 0.5f, 0.1f, 0.5f,
        -0.1f, -0.5f, -0.1f, 0.5f,
        -0.1f, 0.5f, 0.1f, 0.5f,
        -0.1f, -0.5f, -0.1f, 0.5f,
        -0.1f, -0.5f, 0.1f, 0.5f,

        0.1f, 0.5f, -0.1f, 0.5f,
        0.1f, 0.5f, 0.1f, 0.5f,
        0.1f, -0.5f, -0.1f, 0.5f,
        0.1f, 0.5f, 0.1f, 0.5f,
        0.1f, -0.5f, -0.1f, 0.5f,
        0.1f, -0.5f, 0.1f, 0.5f,

        -0.1f, 0.5f, 0.1f, 0.5f,
        -0.1f, 0.5f, -0.1f, 0.5f,
        0.1f, 0.5f, -0.1f, 0.5f,
        -0.1f, 0.5f, 0.1f, 0.5f,
        0.1f, 0.5f, -0.1f, 0.5f,
        0.1f, 0.5f, 0.1f, 0.5f,

        -0.1f, -0.5f, 0.1f, 0.5f,
        -0.1f, -0.5f, -0.1f, 0.5f,
        0.1f, -0.5f, -0.1f, 0.5f,
        -0.1f, -0.5f, 0.1f, 0.5f,
        0.1f, -0.5f, -0.1f, 0.5f,
        0.1f, -0.5f, 0.1f, 0.5f,
    };

    std::vector square_vertices{
        -0.1f, -0.1f, 0.1f, 1.0f,
        -0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, -0.1f, 0.1f, 1.0f,
        -0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, -0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,

        -0.1f, -0.1f, -0.1f, 1.0f,
        -0.1f, 0.1f, -0.1f, 1.0f,
        0.1f, -0.1f, -0.1f, 1.0f,
        -0.1f, 0.1f, -0.1f, 1.0f,
        0.1f, -0.1f, -0.1f, 1.0f,
        0.1f, 0.1f, -0.1f, 1.0f,

        -0.1f, 0.1f, -0.1f, 1.0f,
        -0.1f, 0.1f, 0.1f, 1.0f,
        -0.1f, -0.1f, -0.1f, 1.0f,
        -0.1f, 0.1f, 0.1f, 1.0f,
        -0.1f, -0.1f, -0.1f, 1.0f,
        -0.1f, -0.1f, 0.1f, 1.0f,

        0.1f, 0.1f, -0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, -0.1f, -0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, -0.1f, -0.1f, 1.0f,
        0.1f, -0.1f, 0.1f, 1.0f,

        -0.1f, 0.1f, 0.1f, 1.0f,
        -0.1f, 0.1f, -0.1f, 1.0f,
        0.1f, 0.1f, -0.1f, 1.0f,
        -0.1f, 0.1f, 0.1f, 1.0f,
        0.1f, 0.1f, -0.1f, 1.0f,
        0.1f, 0.1f, 0.1f, 1.0f,

        -0.1f, -0.1f, 0.1f, 1.0f,
        -0.1f, -0.1f, -0.1f, 1.0f,
        0.1f, -0.1f, -0.1f, 1.0f,
        -0.1f, -0.1f, 0.1f, 1.0f,
        0.1f, -0.1f, -0.1f, 1.0f,
        0.1f, -0.1f, 0.1f, 1.0f,
    };

    VertexArray rect_vao;
    VertexArray cube_vao;

    rect_vao.bind();
    VertexBuffer rect_vbo{rect_vertices, 4};
    rect_vbo.set_attrib_pointer<float>(3, 0);
    rect_vbo.set_attrib_pointer<float>(1, 3);

    cube_vao.bind();
    VertexBuffer cube_vbo{square_vertices, 4};
    cube_vbo.set_attrib_pointer<float>(3, 0);
    cube_vbo.set_attrib_pointer<float>(1, 3);

    Shader shader{"../src/vert.glsl", "../src/frag.glsl"};

    glEnable(GL_DEPTH_TEST);

    std::mt19937 rnd{std::random_device{}()};
    std::uniform_real_distribution<> x_distribution{0.1f, 0.3f};
    std::uniform_real_distribution<> y_distribution{0.1f, 0.2f};
    std::uniform_real_distribution<> collision_distribution{-0.1f, 0.1f};
    glm::vec2 cube_vel{x_distribution(rnd), y_distribution(rnd)};
    cube_vel = glm::normalize(cube_vel);

    glm::vec3 player_pos{-1.0f, 0.0f, 0.0f};
    glm::vec3 opponent_pos{1.0f, 0.0f, 0.0f};
    glm::vec3 cube_pos{0.0f, 0.0f, 0.0f};
    unsigned int player_score = 0;
    unsigned int opponent_score = 0;
    bool ai = true;
    bool bounce_flag = true;

    while (!glfwWindowShouldClose(m_window->get_window()))
    {
        if (glfwGetKey(m_window->get_window(), GLFW_KEY_ENTER) == GLFW_PRESS)
        {
            ai = !ai;
        }

        if (glfwGetKey(m_window->get_window(), GLFW_KEY_W) == GLFW_PRESS)
        {
            player_pos.y = std::min(player_pos.y + 0.01f, 1.0f);
        }

        if (glfwGetKey(m_window->get_window(), GLFW_KEY_S) == GLFW_PRESS)
        {
            player_pos.y = std::max(player_pos.y - 0.01f, -1.0f);
        }

        if (ai)
        {
            if (cube_pos.y > opponent_pos.y)
            {
                opponent_pos.y = std::min(opponent_pos.y + 0.01f, 1.0f);
            }
            else
            {
                opponent_pos.y = std::max(opponent_pos.y - 0.01f, -1.0f);
            }
        }
        else
        {
            if (glfwGetKey(m_window->get_window(), GLFW_KEY_UP) == GLFW_PRESS)
            {
                opponent_pos.y = std::min(opponent_pos.y + 0.01f, 1.0f);
            }

            if (glfwGetKey(m_window->get_window(), GLFW_KEY_DOWN) == GLFW_PRESS)
            {
                opponent_pos.y = std::max(opponent_pos.y - 0.01f, -1.0f);
            }
        }

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.bind();

        rect_vao.bind();

        glm::mat4 model{1.0f};
        model = glm::rotate(model, glm::radians(-40.0f), {1.0f, 0.0f, 0.0f});
        model = glm::translate(model, player_pos);
        shader.set_uniform("model", model);

        glm::mat4 view{1.0f};
        view = glm::translate(view, {0.0f, 0.0f, -3.0f});
        shader.set_uniform("view", view);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(m_window->get_width()) / static_cast<float>(m_window->get_height()), 0.1f, 100.0f);
        shader.set_uniform("projection", projection);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        model = glm::mat4{1.0f};
        model = glm::rotate(model, glm::radians(-40.0f), {1.0f, 0.0f, 0.0f});
        model = glm::translate(model, opponent_pos);

        shader.set_uniform("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        cube_vao.bind();

        if (cube_pos.x >= 1.5f)
        {
            player_score++;
            cube_pos = {0.0f, 0.0f, 0.0f};
            cube_vel = {x_distribution(rnd), y_distribution(rnd)};
            cube_vel = glm::normalize(cube_vel);
            bounce_flag = true;
        }
        else if (cube_pos.x <= -1.5f)
        {
            opponent_score++;
            cube_pos = {0.0f, 0.0f, 0.0f};
            cube_vel = {x_distribution(rnd), y_distribution(rnd)};
            cube_vel = glm::normalize(cube_vel);
            bounce_flag = true;
        }

        if (cube_pos.y >= 1.0f || cube_pos.y <= -1.0f)
        {
            cube_vel.y *= -1;
        }

        if (
                player_pos.x < cube_pos.x + cube_width &&
                player_pos.x + rect_width > cube_pos.x &&
                player_pos.y < cube_pos.y + cube_height + 0.4f &&
                player_pos.y + rect_height > cube_pos.y - 0.4f &&
                !bounce_flag
            )
        {
            cube_vel.x *= -1;
            cube_vel += glm::vec2{collision_distribution(rnd), collision_distribution(rnd)};
            bounce_flag = !bounce_flag;
        }

        if (
                opponent_pos.x < cube_pos.x + cube_width &&
                opponent_pos.x + rect_width > cube_pos.x &&
                opponent_pos.y < cube_pos.y + cube_height + 0.4f &&
                opponent_pos.y + rect_height > cube_pos.y - 0.4f &&
                bounce_flag
            )
        {
            cube_vel.x *= -1;
            cube_vel += glm::vec2{collision_distribution(rnd), collision_distribution(rnd)};
            bounce_flag = !bounce_flag;
        }

        cube_pos += glm::vec3{cube_vel.x * 0.02f, cube_vel.y * 0.02f, 0.0f};

        model = glm::mat4{1.0f};
        model = glm::rotate(model, glm::radians(-40.0f), {1.0f, 0.0f, 0.0f});
        model = glm::translate(model, cube_pos);
        shader.set_uniform("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(m_window->get_window());

        glfwPollEvents();
    }

    std::cout << "Player score: " << player_score << "\n"
                << "Opponent score: " << opponent_score << std::endl;
}

Game::~Game()
{
    glfwTerminate();
}

