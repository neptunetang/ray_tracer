//
// Created by neptune on 09-06-20.
//
#include "common_method.h"
#include "../texture/image.h"
void create_scene(vec3 &look_from, vec3& look_at, hitable* &world, light &light_area, int scene){
    material* white = new diffuse(new constant_texture(vec3(1,1,1)));

    int pic_x, pic_y, pic_n;
    unsigned char* texture_data = stbi_load("e.jpg", &pic_x, &pic_y, &pic_n, 0);
    texture* earth_surface = new image_texture(texture_data, pic_x, pic_y);

    int f_x, f_y, f_n;
    unsigned char* fur_data = stbi_load("fur.jpg", &f_x, &f_y, &f_n, 0);
    texture* fur_surface = new image_texture(fur_data, f_x, f_y);

    int m_x, m_y, m_n;
    unsigned char* m_data = stbi_load("m.jpg", &m_x, &m_y, &m_n, 0);
    texture* m_surface = new image_texture(m_data, m_x, m_y);

    texture* checker = new checker_texture(
            new constant_texture(vec3(0.2,0.3,0.1)),
            new constant_texture(vec3(0.9,0.9,0.9))
    );

    int i, n;

    hitable* box1;
    hitable* box2;
    hitable **list;

    switch(scene){
        case 1 :
            list = new hitable*[2];
            list[0] = new sphere(vec3(0,0,-1), 0.5, new metal(new constant_texture(vec3(0.2,0.3,0.0)), 0.0));
            list[1] = new sphere(vec3(0,-100.5,-1), 100, new diffuse(new constant_texture(vec3(0.5,0.5,0.5))));look_from = vec3(0,0,1);

            world = new hitable_list(list, 2);
            break;

        case 2:
            n = 500;
            list = new hitable*[n+1];
            list[0] = new sphere(vec3(0,-1000,0), 1000, new diffuse(new constant_texture(vec3(0.5,0.5,0.5))));
            i = 1;
            for (int a = -10; a < 10; a++){
                for(int b = -10; b < 10; b++){
                    float choose_mat = random_float();
                    vec3 center(a+0.9*random_float(), 0.2, b+0.9*random_float());
                    if((center-vec3(4,0.2,0)).length() > 0.9){
                        if(choose_mat < 0.8){
                            list[i++] = new moving_sphere(center, center+vec3(0, random_float(0,0.5), 0), 0.0, 1.0, 0.2,
                                                          new diffuse(new constant_texture(vec3(random_float()*random_float(),random_float()*random_float(),random_float()*random_float()))));
                        } else if (choose_mat < 0.95){
                            list[i++] = new sphere (center, 0.2, new metal(new constant_texture(vec3(0.5*(1+random_float()), 0.5*(1+random_float()), 0.5*(1+random_float()))),0.5*random_float()));
                        } else {
                            list[i++] = new sphere(center, 0.2, new dielectric(1.5));
                        }
                    }
                }
            }
            look_from = vec3(13,2,3);

            world = new hitable_list(list, i);
            break;

        case 3:
            list = new hitable*[3];
            list[0] = new sphere(vec3(0,1,0), 1.0, new dielectric(1.5));
            list[1] = new moving_sphere(vec3(-4,1,0), vec3(-4,1,1),0.0,1.0, 1.0, new diffuse(new constant_texture(vec3(0.4,0.2,0.1))));
            list[2] = new sphere(vec3(4,1,0), 1.0, new metal(new constant_texture(vec3(0.7, 0.6, 0.5)), 0.0));

            look_from = vec3(13,2,3);
            world = new hitable_list(list, 3);
            break;

        case 5:
            n = 10;
            list = new hitable*[n+1];
            i = 0;
            list[i++] = new flip_face(new yz_rect(0,555,0,555,555, new diffuse(new constant_texture(vec3(0.6,0.3,0.3)))));
            list[i++] = new yz_rect(0,555,0,555,0, new diffuse(new constant_texture(vec3(0.5,0.1,0.5))));
            list[i++] = new xz_rect(0,555,0,555,0, white);
            list[i++] = new flip_face(new xz_rect(0,555,0,555,555, white));
            list[i++] = new xy_rect(0,555,0,555,555, white);

            list[i++] = new flip_face(new xz_rect(0,555,455,555,554,new diffuse_light(new constant_texture(vec3(5,5,5)))));
            light_area = light(new flip_face(new xz_rect(0,555,455,555,554,new diffuse_light(new constant_texture(vec3(5,5,5))))), vec3(5,5,5), 5);

            list[i++] = new sphere(vec3(200,100,200),100, white);


            look_from = vec3(278, 278, -800);
            look_at = vec3(278,278,0);

            world = new hitable_list(list, i);
            break;

        case 4:
            n = 10;
            list = new hitable*[n+1];
            i=0;
            list[i++] = new xz_rect(420,550,400,550,1,new diffuse_light(new constant_texture(vec3(5,0,0))));
            light_area = light(new xz_rect(400,550,400,550,1,new diffuse_light(new constant_texture(vec3(5,0,0)))), vec3(5,5,5), 5);

            list[i++] = new xz_rect(230,360,400,550,1,new diffuse_light(new constant_texture(vec3(0,5,0))));
            light_area = light(new xz_rect(240,390,400,550,1,new diffuse_light(new constant_texture(vec3(0,5,0)))), vec3(5,5,5), 5);

            list[i++] = new xz_rect(40,170,400,550,1,new diffuse_light(new constant_texture(vec3(0,0,5))));
            light_area = light(new xz_rect(80,230,400,550,1,new diffuse_light(new constant_texture(vec3(0,0,5)))), vec3(5,5,5), 5);

            list[i++] = new xy_rect(40,170,0,555,555, white);
            list[i++] = new xy_rect(230,360,0,555,555, white);
            list[i++] = new xy_rect(420,550,0,555,555, white);

            look_from = vec3(278, 278, -700);
            look_at = vec3(278,278,0);

            world = new hitable_list(list, i);
            break;

        case 6:
            n = 10;
            list = new hitable*[n+1];
            i = 0;
            list[i++] = new flip_face(new yz_rect(0,555,0,555,555, new diffuse(new constant_texture(vec3(0.6,0.3,0.3)))));
            list[i++] = new yz_rect(0,555,0,555,0, new diffuse(new constant_texture(vec3(0.5,0.1,0.5))));
            list[i++] = new xz_rect(0,555,0,555,0, white);
            list[i++] = new flip_face(new xz_rect(0,555,0,555,555, white));
            list[i++] = new xy_rect(0,555,0,555,555, white);

//            list[i++] = new flip_face(new yz_rect(200,350,200,350,200, white));
//            list[i++] = new yz_rect(200,350,200,350,350, white);
//            list[i++] = new xy_rect(200,350,200,350,200, white);
//            list[i++] = new flip_face(new xy_rect(200,350,200,350,350, white));
//            list[i++] = new flip_face(new xz_rect(200,350,200,350,200, white));

            list[i++] = new sphere(vec3(275,400,275), 40, new diffuse_light(new constant_texture(vec3(10,10,10))));
            light_area = light(new sphere (vec3(275,400,275), 40, new diffuse_light(new constant_texture(vec3(10,10,10)))),
                               vec3(10,10,10), 10);
            box2 = new box(vec3(0,0,0), vec3(165,100,165), white);
            box2 = new rotate_y(box2, -18);
            list[i++] = new translate(box2, vec3(195,0,65));

            look_from = vec3(278, 278, -800);
            look_at = vec3(278,278,0);

            world = new hitable_list(list, i);
            break;

        case 7:
            n = 100;
            list = new hitable*[n+1];
            i=0;

            box2 = new box(vec3(0,0,0), vec3(50,50,50), new diffuse(new constant_texture(vec3(1,0,0))));
            //R
            list[i++] = new translate(box2, vec3(395,300,65));
            list[i++] = new translate(box2, vec3(395, 400,65));
            list[i++] = new translate(box2, vec3(395, 450,65));
            list[i++] = new translate(box2, vec3(395, 500,65));

            list[i++] = new translate(box2, vec3(445, 350,65));
            list[i++] = new translate(box2, vec3(445, 400,65));
            list[i++] = new translate(box2, vec3(445, 500,65));

            list[i++] = new translate(box2, vec3(495, 300,65));
            list[i++] = new translate(box2, vec3(495, 350,65));
            list[i++] = new translate(box2, vec3(495, 400,65));
            list[i++] = new translate(box2, vec3(495, 450,65));
            list[i++] = new translate(box2, vec3(495, 500,65));

            box2 = new box(vec3(0,0,0), vec3(50,50,50), new diffuse(new constant_texture(vec3(1,0.5,0))));
            //A
            list[i++] = new translate(box2, vec3(335,300,65));
            list[i++] = new translate(box2, vec3(335,350,65));
            list[i++] = new translate(box2, vec3(335,400,65));
            list[i++] = new translate(box2, vec3(335,450,65));

            list[i++] = new translate(box2, vec3(285,400,65));
            list[i++] = new translate(box2, vec3(285,500,65));

            list[i++] = new translate(box2, vec3(235,300,65));
            list[i++] = new translate(box2, vec3(235,350,65));
            list[i++] = new translate(box2, vec3(235,400,65));
            list[i++] = new translate(box2, vec3(235,450,65));

            //Y
            box2 = new box(vec3(0,0,0), vec3(50,50,50), new diffuse(new constant_texture(vec3(1,1,0))));
            list[i++] = new translate(box2, vec3(175,450,65));
            list[i++] = new translate(box2, vec3(175,500,65));

            list[i++] = new translate(box2, vec3(125,300,65));
            list[i++] = new translate(box2, vec3(125,350,65));
            list[i++] = new translate(box2, vec3(125,400,65));

            list[i++] = new translate(box2, vec3(75,450,65));
            list[i++] = new translate(box2, vec3(75,500,65));

            //T
            box2 = new box(vec3(0,0,0), vec3(50,50,50), new diffuse(new constant_texture(vec3(0,1,0))));
            list[i++] = new translate(box2, vec3(720, 200,65));

            list[i++] = new translate(box2, vec3(670, 0,65));
            list[i++] = new translate(box2, vec3(670, 50,65));
            list[i++] = new translate(box2, vec3(670, 100,65));
            list[i++] = new translate(box2, vec3(670, 150,65));
            list[i++] = new translate(box2, vec3(670, 200,65));

            list[i++] = new translate(box2, vec3(620, 200,65));

            //R
            box2 = new box(vec3(0,0,0), vec3(50,50,50), new diffuse(new constant_texture(vec3(0,0.5,1))));
            list[i++] = new translate(box2, vec3(560, 0,65));
            list[i++] = new translate(box2, vec3(560, 50,65));
            list[i++] = new translate(box2, vec3(560, 100,65));
            list[i++] = new translate(box2, vec3(560, 150,65));
            list[i++] = new translate(box2, vec3(560, 200,65));

            list[i++] = new translate(box2, vec3(510, 50,65));
            list[i++] = new translate(box2, vec3(510, 100,65));
            list[i++] = new translate(box2, vec3(510, 200,65));

            list[i++] = new translate(box2, vec3(460,0,65));
            list[i++] = new translate(box2, vec3(460, 100,65));
            list[i++] = new translate(box2, vec3(460, 150,65));
            list[i++] = new translate(box2, vec3(460, 200,65));

            //A
            box2 = new box(vec3(0,0,0), vec3(50,50,50), new diffuse(new constant_texture(vec3(0,0,1))));
            list[i++] = new translate(box2, vec3(400,0,65));
            list[i++] = new translate(box2, vec3(400,50,65));
            list[i++] = new translate(box2, vec3(400,100,65));
            list[i++] = new translate(box2, vec3(400,150,65));

            list[i++] = new translate(box2, vec3(350,100,65));
            list[i++] = new translate(box2, vec3(350,200,65));

            list[i++] = new translate(box2, vec3(300,0,65));
            list[i++] = new translate(box2, vec3(300,50,65));
            list[i++] = new translate(box2, vec3(300,100,65));
            list[i++] = new translate(box2, vec3(300,150,65));

            //C
            box2 = new box(vec3(0,0,0), vec3(50,50,50), new diffuse(new constant_texture(vec3(1,0,1))));
            list[i++] = new translate(box2, vec3(240, 0,65));
            list[i++] = new translate(box2, vec3(240, 50,65));
            list[i++] = new translate(box2, vec3(240, 100,65));
            list[i++] = new translate(box2, vec3(240, 150,65));
            list[i++] = new translate(box2, vec3(240, 200,65));

            list[i++] = new translate(box2, vec3(190, 0,65));
            list[i++] = new translate(box2, vec3(190, 200,65));

            list[i++] = new translate(box2, vec3(140, 0,65));
            list[i++] = new translate(box2, vec3(140, 200,65));

            //E

            box2 = new box(vec3(0,0,0), vec3(50,50,50), new diffuse(fur_surface));
            list[i++] = new translate(box2, vec3(80, 0,65));
            list[i++] = new translate(box2, vec3(80, 50,65));
            list[i++] = new translate(box2, vec3(80, 100,65));
            list[i++] = new translate(box2, vec3(80, 150,65));
            list[i++] = new translate(box2, vec3(80, 200,65));

            list[i++] = new translate(box2, vec3(30, 0,65));
            list[i++] = new translate(box2, vec3(30, 100,65));
            list[i++] = new translate(box2, vec3(30, 200,65));

            list[i++] = new translate(box2, vec3(-20, 0,65));
            list[i++] = new translate(box2, vec3(-20, 100,65));
            list[i++] = new translate(box2, vec3(-20, 200,65));

            //R
            box2 = new box(vec3(0,0,0), vec3(50,50,50), white);
            list[i++] = new translate(box2, vec3(-80, 0,65));
            list[i++] = new translate(box2, vec3(-80, 50,65));
            list[i++] = new translate(box2, vec3(-80, 100,65));
            list[i++] = new translate(box2, vec3(-80, 150,65));
            list[i++] = new translate(box2, vec3(-80, 200,65));

            list[i++] = new translate(box2, vec3(-130, 50,65));
            list[i++] = new translate(box2, vec3(-130, 100,65));
            list[i++] = new translate(box2, vec3(-130, 200,65));

            list[i++] = new translate(box2, vec3(-180,0,65));
            list[i++] = new translate(box2, vec3(-180, 100,65));
            list[i++] = new translate(box2, vec3(-180, 150,65));
            list[i++] = new translate(box2, vec3(-180, 200,65));


            list[i++] = new xy_rect(-280, 900,-100,650,600, white);
            list[i++] = new xy_rect(0,500,0,500,-1350,new diffuse_light(new constant_texture(vec3(5,5,5))));
            light_area = light(new xy_rect(0,500,0,500,-1350,new diffuse_light(new constant_texture(vec3(5,5,5)))), vec3(5,5,5), 5);


            look_from = vec3(278, 278, -1300);
            look_at = vec3(278,278,0);

            world = new hitable_list(list ,i);
            break;

        case 8:
            n = 100;
            list = new hitable*[n+1];
            i = 0;
            list[i++] = new flip_face(new yz_rect(0,555,0,555,555, new diffuse(new constant_texture(vec3(0.6,0.3,0.3)))));
            list[i++] = new yz_rect(0,555,0,555,0, new diffuse(new constant_texture(vec3(0.5,0.1,0.5))));
            list[i++] = new xz_rect(0,555,0,555,0, white);
            list[i++] = new flip_face(new xz_rect(0,555,0,555,555, white));
            list[i++] = new xy_rect(0,555,0,555,555, white);


            //table
            list[i++] = new box(vec3(100,0,100), vec3(130,150,130), white);
            list[i++] = new box(vec3(470,0,470), vec3(500,150,500), white);
            list[i++] = new box(vec3(100,0,470), vec3(130,150,500), white);
            list[i++] = new box(vec3(470,0,100), vec3(500,150,130), white);
            list[i++] = new box(vec3(100,150,100), vec3(500,180,500), white);

            //heart1
            box1 = new box(vec3(0,0,0), vec3(25,25,50), new diffuse(new constant_texture(vec3(1,0,0))));
            box1 = new rotate_y(box1, 10);
            list[i++] = new translate(box1, vec3(200,180,250));

            list[i++] = new translate(box1, vec3(175,205,250));
            list[i++] = new translate(box1, vec3(200,205,250));
            list[i++] = new translate(box1, vec3(225,205,250));

            list[i++] = new translate(box1, vec3(150,230,250));
            list[i++] = new translate(box1, vec3(175,230,250));
            list[i++] = new translate(box1, vec3(200,230,250));
            list[i++] = new translate(box1, vec3(225,230,250));
            list[i++] = new translate(box1, vec3(250,230,250));

            list[i++] = new translate(box1, vec3(125,255,250));
            list[i++] = new translate(box1, vec3(150,255,250));
            list[i++] = new translate(box1, vec3(175,255,250));
            list[i++] = new translate(box1, vec3(200,255,250));
            list[i++] = new translate(box1, vec3(225,255,250));
            list[i++] = new translate(box1, vec3(250,255,250));
            list[i++] = new translate(box1, vec3(275,255,250));

            list[i++] = new translate(box1, vec3(150,280,250));
            list[i++] = new translate(box1, vec3(175,280,250));
            list[i++] = new translate(box1, vec3(200,280,250));
            list[i++] = new translate(box1, vec3(225,280,250));
            list[i++] = new translate(box1, vec3(250,280,250));

            list[i++] = new translate(box1, vec3(175,305,250));
            list[i++] = new translate(box1, vec3(225,305,250));

            //heart2
            box1 = new box(vec3(0,0,0), vec3(25,25,50), new diffuse(new constant_texture(vec3(0,0,1))));
            box1 = new rotate_y(box1, -10);
            list[i++] = new translate(box1, vec3(400,180,250));

            list[i++] = new translate(box1, vec3(375,205,250));
            list[i++] = new translate(box1, vec3(400,205,250));
            list[i++] = new translate(box1, vec3(425,205,250));

            list[i++] = new translate(box1, vec3(350,230,250));
            list[i++] = new translate(box1, vec3(375,230,250));
            list[i++] = new translate(box1, vec3(400,230,250));
            list[i++] = new translate(box1, vec3(425,230,250));
            list[i++] = new translate(box1, vec3(450,230,250));

            list[i++] = new translate(box1, vec3(325,255,250));
            list[i++] = new translate(box1, vec3(350,255,250));
            list[i++] = new translate(box1, vec3(375,255,250));
            list[i++] = new translate(box1, vec3(400,255,250));
            list[i++] = new translate(box1, vec3(425,255,250));
            list[i++] = new translate(box1, vec3(450,255,250));
            list[i++] = new translate(box1, vec3(475,255,250));

            list[i++] = new translate(box1, vec3(350,280,250));
            list[i++] = new translate(box1, vec3(375,280,250));
            list[i++] = new translate(box1, vec3(400,280,250));
            list[i++] = new translate(box1, vec3(425,280,250));
            list[i++] = new translate(box1, vec3(450,280,250));

            list[i++] = new translate(box1, vec3(375,305,250));
            list[i++] = new translate(box1, vec3(425,305,250));

            list[i++] = new box(vec3(20,0,494), vec3(100, 555, 495), white);
            list[i++] = new box(vec3(100, 0, 494), vec3(101,555, 555), white);

            list[i++] = new box(vec3(0,0,554),vec3(60,555,555), new diffuse_light(new constant_texture(vec3(5,5,5))));
            light_area = light(new box(vec3(0,0,554),vec3(60,555,555), new diffuse_light(new constant_texture(vec3(5,5,5)))), vec3(5,5,5), 5);
            look_from = vec3(278, 278, -800);
            look_at = vec3(278,278,0);

            world = new hitable_list(list ,i);
            break;

        case 9:
            n = 5000;
            list = new hitable*[n+1];
            //ground with randomly generated boxes
            i = 0;
            auto ground = new diffuse(new constant_texture(vec3(0.48,0.83,0.53)));
            for(int m=0; m<20; m++){
                for (int n=0; n<20; n++){
                    auto w = 100.0;
                    auto x0 = -1000.0+m*w;
                    auto z0 = -1000.0+n*w;
                    auto y0 = 0.0;
                    auto x1 = x0+w;
                    auto z1 = z0+w;
                    auto y1 = random_float(1,101);
                    list[i++] = new box(vec3(x0,y0,z0), vec3(x1,y1,z1), ground);
                }
            }

            //light emitting rectangle
            auto lighting = new diffuse_light(new constant_texture(vec3(7,7,7)));
            list[i++] = new flip_face(new xz_rect(123,423,147,412,554, lighting));
            light_area = light(new flip_face(new xz_rect(123,423,147,412,554, lighting)), vec3(7,7,7), 7);

            // moving sphere
            auto moving_sphere_material = new diffuse(new constant_texture(vec3(0.7,0.3,0.1)));
            list[i++] = new moving_sphere(vec3(400,400,400), vec3(430,400,200), 0,1,50, moving_sphere_material);

            //earth
            list[i++] = new sphere(vec3(400,200,400), 70, new diffuse(earth_surface));

            //normal sphere
            list[i++] = new sphere(vec3(220,280,300), 80, new diffuse(new constant_texture(vec3(1,1,1))));

            //randomly generated white ball in given area(box)
            auto white = new diffuse(new constant_texture(vec3(1,1,1)));
            for (int k=0; k<100; k++){
                auto x = random_float(0,165);
                auto y = random_float(0,165);
                auto z = random_float(0,165);
                auto small_sphere = new sphere(vec3(x,y,z), 10, white);
                list[i++] = new translate(new rotate_y(small_sphere, 15), vec3(-100,270,395));
            }

            look_from = vec3(478,278,-600);
            look_at = vec3(278,278,0);

            world = new hitable_list(list ,i);
            break;

    }
}