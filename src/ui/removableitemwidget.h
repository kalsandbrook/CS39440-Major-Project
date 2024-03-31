#include <QWidget>
#include <QListWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

class RemovableItemWidget : public QWidget {
    Q_OBJECT
public:
    RemovableItemWidget(const QString &text, QListWidget *parentListWidget);
    QString getText() const;

private:
    QLabel* label;
    QListWidget *listWidget;
};
