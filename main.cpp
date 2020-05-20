#include "debug.hpp"
#include "math.hpp"
#include "timer.hpp"

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using Color = Vec4<u8>;

#define SCREEN_SIZE 128
#define PIXEL_SCALE 4
SDL_Rect pixel_rect = {0, 0, PIXEL_SCALE, PIXEL_SCALE};
Timer timer;
SDL_Surface *texture;

void set_at(SDL_Surface *surface, Vec2<i32> pixel, Vec4<u8> color) {
    pixel_rect.x = pixel.x * PIXEL_SCALE;
    pixel_rect.y = pixel.y * PIXEL_SCALE;
    SDL_FillRect(surface, &pixel_rect, SDL_MapRGBA(surface->format, color.x, color.y, color.z, color.z));
}

void render_world(SDL_Surface* surface);

i32 main(i32 argc, i8* argv[]) {
    SDL_Window *window;
    SDL_Renderer *renderer;
    
    SDL_CreateWindowAndRenderer(SCREEN_SIZE * PIXEL_SCALE, SCREEN_SIZE * PIXEL_SCALE, 0, &window, &renderer);
    
    SDL_Surface* w_sf = SDL_GetWindowSurface(window);
    SDL_Surface *render = SDL_CreateRGBSurface(0, SCREEN_SIZE * PIXEL_SCALE, SCREEN_SIZE * PIXEL_SCALE, 32, 0, 0, 0, 0);
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    
    SDL_Event event;
    bool run = true;
    
    texture = IMG_Load("ground.png");
    
    SDL_Rect rec = {0, 0, SCREEN_SIZE * PIXEL_SCALE, SCREEN_SIZE * PIXEL_SCALE};
    
    while(run) {
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                run = false;
            }
        }
        
        SDL_FillRect(render, &rec, SDL_MapRGBA(render->format, 0, 0, 0, 255));
        
        render_world(render);
        
        SDL_BlitSurface(render, NULL, w_sf, NULL);
        SDL_UpdateWindowSurface(window);
    }
    
    return 0;
}

class Triangle {
public:
    Vec3<f32> a, b, c;
    Vec2<f32> ua, ub, uc;
    Color color;
    
    Triangle(Vec3<f32> _a, Vec3<f32> _b, Vec3<f32> _c) {
        a = _a;
        b = _b;
        c = _c;
    }
};

Vec3<f32> local_rotation;

Vec3<f32> get_pixel(Vec2<f32> uv) {
    int x = texture->w * uv.x;
    int y = texture->h * uv.y;
    
    int bpp = texture->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)texture->pixels + y * texture->pitch + x * bpp;
    
    return {p[0] / 255.0f, p[1] / 255.0f, p[2] / 255.0f};
}

Vec3<f32> shade(Vec2<i32> pixel, Vec3<f32> point, Triangle tri) {
    Vec3<f32> f1 = tri.a - point;
    Vec3<f32> f2 = tri.b - point;
    Vec3<f32> f3 = tri.c - point;
    
    float a = (tri.a - tri.b).cross(tri.a - tri.c).length();
    float a1 = f2.cross(f3).length() / a;
    float a2 = f3.cross(f1).length() / a;
    float a3 = f1.cross(f2).length() / a;
    
    Vec2<f32> uv = tri.ua * a1 + tri.ub * a2 + tri.uc * a3;
    
    return get_pixel(uv);
}

void render_world(SDL_Surface* surface) {
    #define FOVY 45.0f
    #define ASPECT 1
    
    float _sin_time = sin(timer.current());
    
    Ray camera({0, 0, 10}, {0, 0, -1});
    
    // define world
    
    Triangle tri_1({-2, -2, 0}, {2, 0, 0}, {0, 2, 0});
    Triangle tri_2({-2, -2, 0}, {0, 2, 0}, {2, 0, 0});
    
    tri_1.ua = {0, 0};
    tri_1.ub = {1, 0};
    tri_1.uc = {0, 1};
    
    local_rotation.x += 1;
    local_rotation.y += 1;
    local_rotation.z += 1;
    
    // end world
    
    tri_1.a = tri_1.a.rot(local_rotation);
    tri_1.b = tri_1.b.rot(local_rotation);
    tri_1.c = tri_1.c.rot(local_rotation);
    
    camera.origin.z += 2 * _sin_time;
    Vec3<f32> ori = camera.origin;
    Vec3<f32> dir = camera.direction;
    Vec3<f32>* point;
    
    Vec3<f32> delta(FOVY / SCREEN_SIZE, (FOVY * ASPECT) / SCREEN_SIZE);
    Vec3<f32> df((SCREEN_SIZE/2) * delta.y, (SCREEN_SIZE/2) * delta.x, 0);
    
    for(float y = 0; y < SCREEN_SIZE; y++) {
        for(float x = 0; x < SCREEN_SIZE; x++) {
            Vec3<f32> dst(delta.y * y, delta.x * x, 0);
            
            camera.direction = dir.rot(df - dst);
            // camera.direction = camera.direction.rot(local_rotation);
            
            point = camera.intersect_triangle(tri_1.a, tri_1.b, tri_1.c);
            
            if (point) {
                Vec3<f32> s = shade(Vec2<i32>(x, y), *point, tri_1) * 255;
                Color color(s.x, s.y, s.z, 255);
                set_at(surface, Vec2<i32>(x, y), color);
            }
        }
    }
}