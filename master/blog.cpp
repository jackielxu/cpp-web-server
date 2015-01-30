#include <stdio.h>
#include <time.h>
#include <cstdlib>
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

static const char alphanum[] =
"0123456789"
"!@#$%^&*"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

class BlogApp : public Wt::WApplication
{
	public:
		BlogApp(const Wt::WEnvironment& env);

	private:
		Wt::WText *opening_text_;
		Wt::WLineEdit *blogEdit_;
		Wt::WText *title_;
		Wt::WText *post_;
		Wt::WText *intro_;
		Wt::WTextArea *bodyEdit_;
		Wt::WText *bodyPost_;
		Wt::WText *timestamp_;

		void greet();
		void randomness();
		void enter();
		void timestamp();
};

BlogApp::BlogApp(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
{
    setTitle("Coo Coo Ka Shoo");
    Wt::WText *title = new Wt::WText("<h1>A Witty Blog: The Daily Xu</h1>");
    root()->addWidget(title);

    intro_ = new Wt::WText("Welcome to your blog to be. Share your daily happenings and life musings\
    	, from the new tricks in C/C++ that you are learning, to the new napping postiion you have mastered\
    	without hurting your neck, to all of your deepest darkest secrets which \
    	only the people standing behind you will find out about. Start a post and write on!");
    opening_text_->addStyleClass("blogpost");
	opening_text_ = new Wt::WText("Make a new blog post!");

    root()->addWidget(opening_text_);
	opening_text_->addStyleClass("query-words");

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
	Wt::WPushButton *random_button = new Wt::WPushButton("Generate complete random text!", root());
	button->addStyleClass("post");
	random_button->addStyleClass("post");

    root()->addWidget(new Wt::WBreak());

    button->clicked().connect(this, &BlogApp::enter);
	random_button->clicked().connect(this, &BlogApp::randomness);
	blogEdit_->enterPressed().connect(this, &BlogApp::enter);
}

void BlogApp::randomness() {
	std::string title, body;
	
	for (int i = 0; i < 10; i++)
		title += alphanum[rand() % (sizeof(alphanum) - 1)];
	for (int j = 0; j < 100; j++)
		body += alphanum[rand() % (sizeof(alphanum) - 1)];

	root()->addWidget(new Wt::WBreak());
    title_ = new Wt::WText(root());
    title_->setText(title);
    title_->addStyleClass("title");
	root()->addWidget(new Wt::WBreak());
	post_ = new Wt::WText(root());
	post_->setText(body);

	timestamp();

	root()->addWidget(new Wt::WBreak());
	root()->addWidget(new Wt::WBreak());

	blogEdit_->setText("");
	bodyEdit_->setText(""); 

}

void BlogApp::timestamp() {

	root()->addWidget(new Wt::WBreak());
    timestamp_ = new Wt::WText(root());
    timestamp_->addStyleClass("timestamp");
    std::time_t time = std::time(nullptr);
    std::string time_str;
    time_str.append("( ");
    time_str.append(std::asctime(std::localtime(&time)));
    time_str.append(")");
    timestamp_->setText(time_str); 
}

void BlogApp::greet()
{
    root()->addWidget(new Wt::WBreak());
    title_ = new Wt::WText(root());
    title_->setText(blogEdit_->text());
    title_->addStyleClass("title");
	root()->addWidget(new Wt::WBreak());

	post_ = new Wt::WText(root());
	post_->setText(bodyEdit_->text());
	timestamp();
    post_->setText(blogEdit_->text());
}

/*
 * Posts blog post on page, appending to list of blog posts.
 */
void BlogApp::enter()
{
	if (blogEdit_->text().empty() && bodyEdit_->text().empty()) {
		bodyEdit_->setText("");
		return;
	}

    root()->addWidget(new Wt::WBreak());
    title_ = new Wt::WText(root());
    title_->setText(blogEdit_->text());
    title_->addStyleClass("title");
	root()->addWidget(new Wt::WBreak());
	post_ = new Wt::WText(root());
	post_->setText(bodyEdit_->text());
	post_->addStyleClass("blogpost");
	
	timestamp();

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
