#include <stdio.h>
#include <time.h>
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

class BlogApp : public Wt::WApplication
{
	public:
		BlogApp(const Wt::WEnvironment& env);

	private:
		Wt::WText *opening_text_;
		Wt::WLineEdit *blogEdit_;
		Wt::WText *title_;
		Wt::WText *post_;
		Wt::WTextArea *bodyEdit_;
		Wt::WText *bodyPost_;
		Wt::WText *timestamp_;

		void greet();
		void enter();
};

BlogApp::BlogApp(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
{
    setTitle("Coo Coo Ka Shoo");
    Wt::WText *title = new Wt::WText("<h1>A Witty Blog: The Daily Xu</h1>");
    root()->addWidget(title);

	opening_text_ = new Wt::WText("Make a new blog post!");

    root()->addWidget(opening_text_);
	opening_text_->addStyleClass("post");

    root()->addWidget(new Wt::WBreak());
    blogEdit_ = new Wt::WLineEdit(root());
	blogEdit_->addStyleClass("post");

	root()->addWidget(new Wt::WBreak());
	bodyEdit_ = new Wt::WTextArea(root());
	bodyEdit_->setColumns(80);
	bodyEdit_->setRows(5);
	bodyEdit_->setText("");
	bodyEdit_->addStyleClass("post");

	root()->addWidget(new Wt::WBreak());
    Wt::WPushButton *button = new Wt::WPushButton("Enter post.", root());
	button->addStyleClass("post");

    root()->addWidget(new Wt::WBreak());

    post_ = new Wt::WText(root());
    button->clicked().connect(this, &BlogApp::enter);
	blogEdit_->enterPressed().connect(this, &BlogApp::enter);
}

void BlogApp::greet()
{
    root()->addWidget(new Wt::WBreak());
    title_ = new Wt::WText(root());
    title_->setText(blogEdit_->text());
	root()->addWidget(new Wt::WBreak());

	post_ = new Wt::WText(root());
	post_->setText(bodyEdit_->text());

	root()->addWidget(new Wt::WBreak());
    timestamp_ = new Wt::WText(root());
    timestamp_->addStyleClass("timestamp");

    std::time_t time = std::time(nullptr);
    std::string time_str;

    time_str.append("( ");
    time_str.append(std::asctime(std::localtime(&time)));
    time_str.append(")");
    timestamp_->setText(time_str);

    post_->setText(blogEdit_->text());
}

/*
 * Posts blog post on page, appending to list of blog posts.
 */
void BlogApp::enter()
{
    root()->addWidget(new Wt::WBreak());
    title_ = new Wt::WText(root());
    title_->setText(blogEdit_->text());
	root()->addWidget(new Wt::WBreak());
	post_ = new Wt::WText(root());
	post_->setText(bodyEdit_->text());

	// Timestamp
	root()->addWidget(new Wt::WBreak());
    timestamp_ = new Wt::WText(root());
    timestamp_->addStyleClass("timestamp");
    std::time_t time = std::time(nullptr);
    std::string time_str;
    time_str.append("( ");
    time_str.append(std::asctime(std::localtime(&time)));
    time_str.append(")");
    timestamp_->setText(time_str);

	root()->addWidget(new Wt::WBreak());
	root()->addWidget(new Wt::WBreak());

	blogEdit_->setText("");
	bodyEdit_->setText(""); 
}

Wt::WApplication *createApplication(const Wt::WEnvironment& env)
{
    Wt::WApplication *app = new BlogApp(env);

    app->useStyleSheet("blog.css");
    return app;
}

int main(int argc, char **argv)
{
    return Wt::WRun(argc, argv, &createApplication);
}
