class HangmanWidget : public Wt::WContainerWidget
{
public:
    HangmanWidget(const std::string &name, Wt::WContainerWidget *parent = 0);

    Wt::Signal<int>& scoreUpdated() { return scoreUpdated_; }

private:
    Wt::WText        *title_;
    WordWidget       *word_;
    ImagesWidget     *images_;
    LettersWidget    *letters_;
    Wt::WText        *statusText_;
    Wt::WComboBox    *language_;
    Wt::WPushButton  *newGameButton_;

    Wt::Signal<int>   scoreUpdated_;

    std::string       name_;
    Dictionary        dictionary_;
    int               badGuesses_;

    void registerGuess(char c);
    void newGame();
};

using namespace Wt;

HangmanWidget::HangmanWidget(const std::string &name, WContainerWidget *parent)
    : WContainerWidget(parent),
      name_(name),
      badGuesses_(0)
{
    setContentAlignment(AlignCenter);

    title_ = new WText(tr("hangman.readyToPlay"), this);

    word_ = new WordWidget(this);
    statusText_ = new WText(this);
    images_ = new ImagesWidget(MaxGuesses, this);

    letters_ = new LettersWidget(this);
    letters_->letterPushed().connect(this, &HangmanWidget::registerGuess);

    language_ = new WComboBox(this);
    language_->addItem(tr("hangman.englishWords").arg(18957));
    language_->addItem(tr("hangman.dutchWords").arg(1688));

    new WBreak(this);

    newGameButton_ = new WPushButton(tr("hangman.newGame"), this);
    newGameButton_->clicked().connect(this, &HangmanWidget::newGame);

    letters_->hide();
}

void HangmanWidget::newGame()
{
    WString title(tr("hangman.guessTheWord"));
    title_->setText(title.arg(name_));

    language_->hide();
    newGameButton_->hide();

    Dictionary dictionary = (Dictionary) language_->currentIndex();
    word_->init(RandomWord(dictionary));
    letters_->reset();
    badGuesses_ = 0;
    images_->showImage(badGuesses_);
    statusText_->setText("");
}

void HangmanWidget::registerGuess(char c)
{
    bool correct = word_->guess(c);

    if (!correct) {
        ++badGuesses_;
        images_->showImage(badGuesses_);
    }

    if (badGuesses_ == MaxGuesses) {
        WString status(tr("hangman.youHang"));
        statusText_->setText(status.arg(word_->word()));

        letters_->hide();
        language_->show();
        newGameButton_->show();

        scoreUpdated_.emit(-10);
    } else if (word_->won()) {
        statusText_->setText(tr("hangman.youWin"));
        images_->showImage(ImagesWidget::HURRAY);

        letters_->hide();
        language_->show();
        newGameButton_->show();

        scoreUpdated_.emit(20 - badGuesses_);
    }
}


ImagesWidget::ImagesWidget(int maxGuesses, WContainerWidget *parent)
    : WContainerWidget(parent)
{
    for (int i = 0; i <= maxGuesses; ++i) {
        std::string fname = "icons/hangman";
        fname += boost::lexical_cast<std::string>(i) + ".png";
        WImage *theImage = new WImage(fname, this);
        images_.push_back(theImage);

        theImage->hide();
    }

    WImage *hurray = new WImage("icons/hangmanhurray.jpg", this);
    hurray->hide();
    images_.push_back(hurray);

    showImage(HURRAY);
}

void ImagesWidget::showImage(int index)
{
    image(index)->hide();
    image_ = index;
    image(index)->show();
}

WImage *ImagesWidget::image(int index) const
{
    return index == HURRAY ? images_.back() : images_[index];
}

void HangmanGame::handleInternalPath(const std::string &internalPath)
{
    if (session_.login().loggedIn()) {
        if (internalPath == "/play")
            showGame();
        else if (internalPath == "/highscores")
            showHighScores();
        else
            WApplication::instance()->setInternalPath("/play",  true);
    }
}