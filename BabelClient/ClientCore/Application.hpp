#pragma once

#include <QApplication>
#include "IGraphics.hpp"

class Application : public IGraphics
{
    public:
        Application(int ac, char **av) {
            app = new QApplication(ac, av);
        }
        int init() {
            return (app->exec());
        }
        void showApp() {}
    private:
        QApplication *app;
};