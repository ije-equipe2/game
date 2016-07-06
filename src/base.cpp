#include "base.h"
#include "ije02_game.h"

#include <ijengine/canvas.h>

#define MAX_LIFE 1000
#define X_ADJUSTMENT 16.0
#define Y_ADJUSTMENT 20.0
Base::Base(int player_id)
    :m_player_id(player_id), m_life(MAX_LIFE), m_frame(0), m_start(-1)
{
    m_sprite_paths.push_back("Spritesheets/Green/SpritesheetGreenBase.png");
    m_sprite_paths.push_back("Spritesheets/Blue/SpritesheetBlueBase.png");
    m_sprite_paths.push_back("Spritesheets/Yellow/SpritesheetYellowBase.png");
    m_sprite_paths.push_back("Spritesheets/Red/SpritesheetRedBase.png");

    m_texture = resources::get_texture(m_sprite_paths[player_id]);

    m_w = 32;
    m_h = 32;

    set_base_position(player_id, m_x, m_y);

    m_bounding_box = Rectangle(m_x, m_y, 20, 12);

    physics::register_object(this);
}

Base::~Base()
{
    physics::unregister_object(this);
}

void
Base::update_self(unsigned now, unsigned last)
{

}

void
Base::draw_self(Canvas *canvas, unsigned, unsigned)
{
    Rectangle rect {(double) m_w * m_frame, (double) m_h, (double) m_w, (double) m_h};
    canvas->draw(m_texture.get(), rect, x(), y());
}

void
Base::set_base_position(unsigned player_id, double& x_pos, double& y_pos)
{
    switch(player_id) {
        case PLAYER_1:
            x_pos = X_ADJUSTMENT;
            y_pos = Y_ADJUSTMENT;
            break;

        case PLAYER_2:
            x_pos = (double) SCREEN_WIDTH - 32.0 - X_ADJUSTMENT;
            y_pos = Y_ADJUSTMENT;
            break;

        case PLAYER_3:
            x_pos = X_ADJUSTMENT;
            y_pos = (double) SCREEN_HEIGHT - 32.0 - Y_ADJUSTMENT;
            break;

        case PLAYER_4:
            x_pos = (double) SCREEN_WIDTH - 32.0 - X_ADJUSTMENT;
            y_pos = (double) SCREEN_HEIGHT - 32.0 - Y_ADJUSTMENT;
            break;

        default:
            printf("Valor errado no set_base_position_position!\n");
            printf("player_id: %d", player_id);
            break;
    }
}

bool
Base::active() const 
{
    return true;
}

const Rectangle&
Base::bounding_box() const 
{
    return m_bounding_box;
}

const list<Rectangle>&
Base::hit_boxes() const 
{
    static list<Rectangle> boxes {m_bounding_box};
    return boxes;
}

void
Base::on_collision(const Collidable *who, const Rectangle& where, unsigned now, unsigned last)
{
    printf("Colidiu com a base do player %d\n", m_player_id);
}

pair<double, double>
Base::direction() const
{
    return pair<double, double>(m_x_speed, m_y_speed);
}