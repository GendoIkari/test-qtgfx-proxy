#include "v4widget.h"

#include <QCoreApplication>
#include <QDebug>
#include <QHBoxLayout>
#include <QMouseEvent>

V4Widget::V4Widget(QWidget* parent)
    : QWidget(parent)
{
    setLayout(new QHBoxLayout(this));
    layout()->addWidget(&graphicsView);

    webView = new QWebEngineView();
    graphicsView.setScene(&graphicsScene);
    graphicsProxy = graphicsScene.addWidget(webView);
    graphicsProxy->installEventFilter(this);
    webView->setUrl(QUrl("http://google.it"));

    connect(webView, &QWebEngineView::loadFinished, this, &V4Widget::sync);
    connect(webView, &QWebEngineView::loadProgress, this, &V4Widget::sync);
}

bool V4Widget::eventFilter(QObject*, QEvent* event)
{
    // Avoid infinite recursion with QEvent::SetCursor
    if (event->type() == QEvent::GraphicsSceneHoverMove) {
        graphicsProxy->setCursor(webViewInnerWidget()->cursor());
    }

    sync();
    return false;
}

void V4Widget::focusInEvent(QFocusEvent*)
{
    if (webView)
        webViewInnerWidget()->setFocus();
}

void V4Widget::resizeEvent(QResizeEvent*)
{
    graphicsScene.setSceneRect(0, 0, graphicsView.width() - 9, graphicsView.height() - 9);
    webView->setGeometry(0, 0, 1024, 768);
}

QWidget* V4Widget::webViewInnerWidget()
{
    QWidget* target = nullptr;
    for (auto obj : webView->children()) {
        target = qobject_cast<QWidget*>(obj);
        if (target) {
            Q_ASSERT(QString(obj->metaObject()->className()) == "QtWebEngineCore::RenderWidgetHostViewQtDelegateWidget");
            break;
        }
    }
    return target;
}

void V4Widget::sync()
{
    webView->update();
}
