#pragma once

#include <QEvent>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWebEngineView>
#include <QWidget>

class V4Widget : public QWidget {
    Q_OBJECT
public:
    explicit V4Widget(QWidget* parent = nullptr);
    bool eventFilter(QObject* obj, QEvent* event) override;
    void focusInEvent(QFocusEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    QWebEngineView* webView;
    QGraphicsView graphicsView;
    QGraphicsScene graphicsScene;
    QGraphicsProxyWidget* graphicsProxy;

    QWidget* webViewInnerWidget();

private slots:
    void sync();
};
