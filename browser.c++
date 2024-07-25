#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <QLineEdit>
#include <QWebEngineView>

class Browser : public QMainWindow {
    Q_OBJECT

public:
    Browser() {
        view = new QWebEngineView(this);
        view->setUrl(QUrl("http://www.google.com"));
        setCentralWidget(view);

        QToolBar *navbar = addToolBar("Navigation");

        QAction *back = new QAction("Back", this);
        connect(back, &QAction::triggered, view, &QWebEngineView::back);
        navbar->addAction(back);

        QAction *forward = new QAction("Forward", this);
        connect(forward, &QAction::triggered, view, &QWebEngineView::forward);
        navbar->addAction(forward);

        QAction *reload = new QAction("Reload", this);
        connect(reload, &QAction::triggered, view, &QWebEngineView::reload);
        navbar->addAction(reload);

        QAction *home = new QAction("Home", this);
        connect(home, &QAction::triggered, this, &Browser::navigate_home);
        navbar->addAction(home);

        url_bar = new QLineEdit(this);
        connect(url_bar, &QLineEdit::returnPressed, this, &Browser::navigate_to_url);
        navbar->addWidget(url_bar);

        connect(view, &QWebEngineView::urlChanged, this, &Browser::update_url);
    }

private slots:
    void navigate_home() {
        view->setUrl(QUrl("http://www.google.com"));
    }

    void navigate_to_url() {
        QUrl url = QUrl::fromUserInput(url_bar->text());
        view->setUrl(url);
    }

    void update_url(const QUrl &url) {
        url_bar->setText(url.toString());
    }

private:
    QWebEngineView *view;
    QLineEdit *url_bar;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Browser browser;
    browser.show();
    return app.exec();
}

#include "main.moc"