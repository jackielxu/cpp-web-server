#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
//#include <Wt/WEnvironment>
#include <Wt/WPushButton>
//#include <Wt/WServer>
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
		//something
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
	//int post_title->textSize() = 20; 			// trying to incr text size
	
	// // Text box for blog entries
	 root()->addWidget(new WBreak());
	 WContainerWidget *container = new WContainerWidget();
	 WTextArea *post_entry_ = new WTextArea(container);
	 post_entry_->setColumns(80);
	 post_entry_->setRows(5);
	 post_entry_->setText("Write here...");
	 //WTextEdit *post_entry_ = new WTextEdit(container);
	// post_entry_->setHeight(300);

	root()->addWidget(new WBreak());
	WPushButton *button = new WPushButton("Post Title", root());
	// WPushButton *button2 = new WPushButton("Post Entry", container);
	// button2->setMargin(10, Top|Bottom);

	 WText *out = new WText("<p></p>", container);
	 out->addStyleClass("help-block");

	root()->addWidget(new WBreak());
	title_ = new WText(root());
	// entry_ = new WText(container);
	button->clicked().connect(this, &MyApplication::post);
	// post_entry_->changed().connect(bind([=] () {
	//     out->setText("<p>Text area changed at " +
	//          WDateTime::currentDateTime().toString() + ".</p>");
	// }));


	// button->clicked().connect(bind([=] () {
	// 	out->setText("<pre>" + Utils::htmlEncode(post_entry_->text()) + "</pre>");
	// }));

}


void MyApplication::post() {
	title_->setText(post_title_->text());
	entry_->setText(post_entry_->text());
}

WApplication *createApplication(const WEnvironment& env) {
	return new MyApplication(env);
}

int main(int argc, char **argv) {
	return WRun(argc, argv, &createApplication);
}
