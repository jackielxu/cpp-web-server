#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WLineEdit>
#include <Wt/WTextEdit>
#include <Wt/WTextArea>
#include <Wt/WDateTime>
#include <Wt/Utils>

using namespace Wt;
using namespace std;

class MyApplication : public WApplication {
	public:
		MyApplication(const WEnvironment& env);
	private:
		WLineEdit *post_title_;
		WTextEdit *post_entry_;
		WText *title_;
		WText *entry_;

		void post();
};

MyApplication::MyApplication(const WEnvironment& env)
	: WApplication(env) 
{
	setTitle("Dear Diary");

	root()->addWidget(new WText("Title: "));
	post_title_ = new WLineEdit(root());
	
	// // Text box for blog entries
	 root()->addWidget(new WBreak());

	root()->addWidget(new WBreak());
	WPushButton *button = new WPushButton("Post", root());

	root()->addWidget(new WBreak());
	title_ = new WText(root());
	button->clicked().connect(this, &MyApplication::post);

}

void MyApplication::post() {
	title_->setText(post_title_->text());
}

WApplication *createApplication(const WEnvironment& env) {
	return new MyApplication(env);
}

int main(int argc, char **argv) {
	return WRun(argc, argv, &createApplication);
}
