#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include <core/board.h>

using namespace ci;
using namespace ci::app;



class BasicApp : public App {
 public:
  void setup() override;

  void update() override;

  void draw() override;

  template <typename C>
  void PrintText(const std::string &text, const C &color,
                 const cinder::ivec2 &size, const cinder::vec2 &loc,
                 const int font_size = 30) {
    cinder::gl::color(color);

    auto box = TextBox()
        .alignment(TextBox::CENTER)
        .font(cinder::Font("Arial", font_size))
        .size(size)
        .color(color)
        .backgroundColor(ColorA(0, 0, 0, 1))
        .text(text);

    const auto box_size = box.getSize();
    const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
    const auto surface = box.render();
    const auto texture = cinder::gl::Texture::create(surface);
    cinder::gl::draw(texture, locp);
  }

  //void keyDown(KeyEvent event) override;

  //void DrawNextPiece(int col);

  //void mouseMove(MouseEvent event) override;

  void mouseDown(MouseEvent event) override;

  static void prepareSettings(BasicApp::Settings* settings) {
    settings->setMultiTouchEnabled(false);
  }

 private:
  void DrawPieces(connect::Board board);

  connect::Board game;
};
void BasicApp::setup() {
 game.NewGame();
}

void BasicApp::update() {
  if (game.IsGameEnd()) {
    gl::clear();
    //PrintText("GAME OVER", cinder::Color("green"), ivec2(20), ivec2(getWindowCenter()) );
    vec2 center = getWindowCenter();
    float r = 100;

    gl::color( Color( 1, 0, 0 ) ); // red
    gl::drawSolidCircle( center + vec2( -r, r ), r );
  } else {
    if (game.GetCurrentPlayer() == 2) {
      game.Move(2, game.Minimax(game, 5, 0, 0, true)[0]);
    }
  }
}

void BasicApp::draw()
{
  gl::clear();
  // reset the matrices
  gl::setMatricesWindow( getWindowSize() );


  gl::color( 0, 0, 1 ); // set color to blue
  gl::drawSolidRect( Rectf( getWindowWidth()/2- 700.0f,
                            getWindowHeight()/2-400.0f,
                            getWindowWidth()/2+700.0f,
                            getWindowHeight()/2+400.0f ) );

  gl::setMatricesWindow( getWindowSize() );
  //gl::drawSolidCircle( vec2(getWindowWidth()/2,getWindowHeight()/2), 50 );

  // move to the horizontal window center, down 75

  for (int r = 0; r < 6; r++) {
    //gl::translate( 0, 130 );
    for (int c = 0; c < 7; c++) {
      //gl::translate( 130, 0 );
      gl::color( Color( 0, 0, 0 ) );
      gl::drawSolidCircle( vec2(c* (getWindowWidth()  /7 ) + 70,r*(getWindowHeight()  /6 )+ 70), 60 );
    }
    //gl::translate( -130*7, 0 );
  }
  //gl::translate( 0, -130*6 );
  DrawPieces(game);
  //gl::translate(130*3, -130*5);
  gl::color( Color( 1, 0, 0 ) );
  gl::drawSolidCircle( getMousePos(), 60 );
  game.PrintBoard();
}

void BasicApp::DrawPieces(connect::Board board) {
  //std::vector<int> current_pos= {0, 0};
  for (int r = 0; r < 6; r++) {
    for (int c = 0; c < 7; c++) {
      if (board.GetBoard()[r][c] == 1) {
        //gl::translate( 130*(r), 130*(c) );
        gl::color( Color( 1, 0, 0 ) );
        gl::drawSolidCircle( vec2(c* (getWindowWidth()  /7 ) + 70,r*(getWindowHeight()  /6 )+ 70), 60 );
        //gl::drawSolidCircle( vec2( 0 ), 65 );
        //gl::translate(-r*130, -c*130);

      } else if (board.GetBoard()[r][c] == 2) {
        //gl::translate( 130*(r ), 130*(c) );
        gl::color( Color( 1, 1, 0 ) );
        gl::drawSolidCircle( vec2(c* (getWindowWidth()  /7 ) + 70,r*(getWindowHeight()  /6 )+ 70), 60 );
        //gl::drawSolidCircle( vec2( 0 ), 65 );
        //gl::translate(-r*130, -c*130);
      }
    }
  }

}
void BasicApp::mouseDown(MouseEvent event) {
  int col = (getMousePos()[0] /(getWindowWidth()  /7 ));
  game.Move(1, col);
}


CINDER_APP( BasicApp, RendererGl, BasicApp::prepareSettings )