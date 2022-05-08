#ifndef _APP_HPP
#define _APP_HPP

class App {
public:
  App(int width, int height);
  virtual void init() = 0;
  virtual void update() = 0;
  virtual void draw() = 0;
  void run();
private:
  int width, height;

};

#endif
