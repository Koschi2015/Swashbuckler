#ifndef APP_HPP
#define APP_HPP

class App
{
private:
    void update();
    void draw();

    bool m_quit;
public:
    App();

    void run();
};

#endif