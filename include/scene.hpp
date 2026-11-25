#pragma once
#include "general_utils/vec3.hpp"
#include "scene_utils/camera.hpp"
#include "scene_utils/light.hpp"
#include "shapes/shape.hpp"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <memory>
#include <vector>

class Scene {
      private:
        std::vector<std::shared_ptr<Shape>> objects;
        std::vector<std::shared_ptr<Light>> lights;
        SDL_Window **window;
        SDL_Renderer **renderer;
        double aspect_ratio;
        int window_width;
        int window_height;
        double viewport_height;
        double viewport_width;
        double distance_viewport;
        Camera eye;
        Vec3 pixel_delta_horizontal;
        Vec3 pixel_delta_vertical;
        Vec3 pixel00_loc;
        Vec3 ambient_light;
        Vec3 pixelColor(std::shared_ptr<Shape> s, Vec3 &dir,
                        Interseption interseption);

      public:
        Scene(SDL_Window **window, SDL_Renderer **renderer, double aspect_ratio,
              int window_width, double viewport_height,
              double distance_viewport, Camera eye);
        int getWidth();
        int getHeight();
        void addObject(std::shared_ptr<Shape> object);
        void addLight(std::shared_ptr<Light> light);
        void setAmbientLight(Vec3 light);
        void drawFrame();
};
