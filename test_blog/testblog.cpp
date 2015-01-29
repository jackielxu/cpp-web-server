// to run:  
// g++ testblog.cpp -o testblog -I/usr/local/include -L/usr/local/lib -lwthttp -lwt -lboost_random -lboost_regex -lboost_signals -lboost_system -lboost_filesystem -lboost_program_options -lboost_date_time 

#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WCssDecorationStyle>
#include <time.h>
#include <stdio.h>


class HelloApplication : public Wt::WApplication
{
public:
    HelloApplication(const Wt::WEnvironment& env);

private:
    Wt::WLineEdit *blogEdit_;
    Wt::WText *post_;
    Wt::WText *timestamp_;

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
    root()->addWidget(new Wt::WBreak());

    // Timestamp
    timestamp_ = new Wt::WText(root());
    std::time_t time = std::time(nullptr);
    std::string time_str;
    time_str.append("( ");
    time_str.append(std::asctime(std::localtime(&time)));
    time_str.append(")");
    timestamp_->setText(time_str);

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


