#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WCssDecorationStyle>

class HelloApplication : public Wt::WApplication
{
public:
    HelloApplication(const Wt::WEnvironment& env);

private:
    Wt::WLineEdit *blogEdit_;
    Wt::WText *post_;

    void greet();
	void enter();
};

HelloApplication::HelloApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
{
    setTitle("Coo Coo Ka Shoo");
    Wt::WText *title = new Wt::WText("<h1>A Witty Blog: The Daily Xu</h1>");
    root()->addWidget(title);

    root()->addWidget(new Wt::WText("Blog Post: "));
    blogEdit_ = new Wt::WLineEdit(root());
    Wt::WPushButton *button = new Wt::WPushButton("Enter post.", root());
    root()->addWidget(new Wt::WBreak());
    post_ = new Wt::WText(root());
    button->clicked().connect(this, &HelloApplication::enter);
  	blogEdit_->enterPressed().connect(this, &HelloApplication::enter);
}

void HelloApplication::greet()
{
    post_->setText(blogEdit_->text());
}

void HelloApplication::enter()
{ 
    root()->addWidget(new Wt::WBreak());
    post_ = new Wt::WText(root());
    post_->setText(blogEdit_->text()); 
}	

Wt::WApplication *createApplication(const Wt::WEnvironment& env)
{
    Wt::WApplication *app = new HelloApplication(env);
  
    app->useStyleSheet("hello.css");
    return app;
}

int main(int argc, char **argv)
{
    return Wt::WRun(argc, argv, &createApplication);
} 