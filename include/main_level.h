#ifndef MAIN_LEVEL_H
#define MAIN_LEVEL_H

#include <ijengine/level.h>
#include <ijengine/texture.h>
#include <ijengine/event.h>

#include <string>
#include <memory>
#include <vector>

using std::string;
using std::vector;
using std::shared_ptr;

using ijengine::Level;
using ijengine::Canvas;
using ijengine::Texture;
using ijengine::Event;

#define MAX_W 21
#define MAX_H 11

class MainLevel : public Level {
public:
	MainLevel(int r, int g, int b, const string& next = "");
    ~MainLevel();
    
	bool done() const;
	string next() const;

protected:
	void update_self(unsigned now, unsigned last);
	void draw_self(Canvas *canvas, unsigned now, unsigned last);

private:
	int m_r, m_g, m_b;
    bool m_done;
    string m_next;
    int m_start;

    vector< shared_ptr<Texture> > m_textures;
    int m_map[MAX_W][MAX_H];

    inline vector< vector<Event *> > define_controls();
};

#endif
