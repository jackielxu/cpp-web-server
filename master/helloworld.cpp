#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WCssDecorationStyle>
#include <Wt/WText>
#include <Wt/WTextArea>
#include <Wt/WDateTime>

class HelloApplication : public Wt::WApplication
{
	public:
		HelloApplication(const Wt::WEnvironment& env);

	private:
		Wt::WLineEdit *blogEdit_;
		Wt::WText *title_;
		Wt::WText *post_;
		Wt::WTextArea *bodyEdit_;
		Wt::WText *bodyPost_;

		void greet();
		void enter();
};

HelloApplication::HelloApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
{
    setTitle("Coo Coo Ka Shoo");
    Wt::WText *title = new Wt::WText("<h1>A Witty Blog: The Daily Xu</h1>");
    root()->addWidget(title);

    root()->addWidget(new Wt::WText("Blog Title: "));
    root()->addWidget(new Wt::WBreak());
    blogEdit_ = new Wt::WLineEdit(root());
	blogEdit_->addStyleClass("post");

	root()->addWidget(new Wt::WBreak());
	bodyEdit_ = new Wt::WTextArea(root());
	bodyEdit_->setColumns(80);
	bodyEdit_->setRows(5);
	bodyEdit_->setText("Enter body of post!");
	bodyEdit_->addStyleClass("post");

	root()->addWidget(new Wt::WBreak());
    Wt::WPushButton *button = new Wt::WPushButton("Enter post.", root());
	button->addStyleClass("post");
	
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
    title_ = new Wt::WText(root());
    title_->setText(blogEdit_->text()); 
	root()->addWidget(new Wt::WBreak());
	post_ = new Wt::WText(root());
	post_->setText(bodyEdit_->text());
	root()->addWidget(new Wt::WBreak());
	root()->addWidget(new Wt::WBreak());

	blogEdit_->setText("New title");
	bodyEdit_->setText("New body");
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
