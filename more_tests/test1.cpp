/*
 * Copyright (C) 2008 Emweb bvba, Heverlee, Belgium.
 *
 * See the LICENSE file for terms of use.
 */

#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>

// c++0x only, for std::bind
// #include <functional>

using namespace Wt;

/*
 * A simple hello world application class which demonstrates how to react
 * to events, read input, and give feed-back.
 */
class HelloApplication : public WApplication
{
	public:
	  HelloApplication(const WEnvironment& env);

	private:
	  WLineEdit *nameEdit_;
	  WLineEdit *nameSuperEdit_;
	  WText *greeting_;
	  WText *greetingSuper_;

	void greet();
};

/*
 * The env argument contains information about the new session, and
 * the initial request. It must be passed to the WApplication
 * constructor so it is typically also an argument for your custom
 * application constructor.
*/
HelloApplication::HelloApplication(const WEnvironment& env)
  : WApplication(env)
{
  setTitle("Hello world");                               // application title

  root()->addWidget(new WText("Your name, please ? "));  // show some text
  nameEdit_ = new WLineEdit(root());                     // allow text input
  root()->addWidget(new WBreak());
  nameSuperEdit_ = new WLineEdit(root());                     // allow text input
  nameSuperEdit_->setFocus();                                 // give focus

  WPushButton *button
    = new WPushButton("Greet me.", root());              // create a button
  button->setMargin(5, Left);                            // add 5 pixels margin

  root()->addWidget(new WBreak());

  root()->addWidget(new WText("AND YOUR NAME????? "));  // show some text

  WPushButton *button1
    = new WPushButton("Say goodbye.", root());              // create a button
  button1->setMargin(10, Left);                            // add 5 pixels margin 

  root()->addWidget(new WBreak());                       // insert a line break

  greeting_ = new WText(root());                         // empty text

  root()->addWidget(new WBreak());

  greetingSuper_ = new WText(root());

  /*
   * Connect signals with slots
   *
   * - simple Wt-way
   */
  button->clicked().connect(this, &HelloApplication::greet);

  /*
   * - using an arbitrary function object (binding values with boost::bind())
   */
	nameEdit_->enterPressed().connect
    (boost::bind(&HelloApplication::greet, this));
	nameSuperEdit_->enterPressed().connect
    (boost::bind(&HelloApplication::greet, this)); 

  /*
   * - using a c++0x lambda:
   */
  // b->clicked().connect(std::bind([=]() { 
  //       greeting_->setText("Hello there, " + nameEdit_->text());
  // }));
}

void HelloApplication::greet()
{
  /*
   * Update the text, using text input into the nameEdit_ field.
   */
  greeting_->setText("Hello there, " + nameEdit_->text() + "\n");
  greetingSuper_->setText("Bye bye, " + nameSuperEdit_->text() + "\n");
}

WApplication *createApplication(const WEnvironment& env)
{
  /*
   * You could read information from the environment to decide whether
   * the user has permission to start a new application
   */
  return new HelloApplication(env);
}

int main(int argc, char **argv)
{
  /*
   * Your main method may set up some shared resources, but should then
   * start the server application (FastCGI or httpd) that starts listening
   * for requests, and handles all of the application life cycles.
   *
   * The last argument to WRun specifies the function that will instantiate
   * new application objects. That function is executed when a new user surfs
   * to the Wt application, and after the library has negotiated browser
   * support. The function should return a newly instantiated application
   * object.
   */
  return WRun(argc, argv, &createApplication);
}

