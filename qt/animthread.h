#ifndef ANIMTHREAD_H
#define ANIMTHREAD_H

#include <QThread>
#include "sc_window.h"

class AnimThread : public QThread {
    Q_OBJECT
    void run();
public:
    SC_Window* window;
    bool active;
};

#endif // ANIMTHREAD_H

