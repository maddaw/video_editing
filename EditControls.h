#ifndef EDITCONTROLS_H
#define EDITCONTROLS_H



class EditControls : public QWidget
{
    public:
        EditControls(QWidget *parent);
    private:
        QVBoxLayout *mainLayout;

        QHBoxLayout *topLayout;
        QHBoxLayout *bottomLayout;

        QPushButton *cutMedia;

        QListWidget *mediaList;
        QSlider *videoSlider;

    protected slots:
        void cutReleased();
        void selectReleased();

    public slots:

    signals:
        void cutMediaSignal(QString);

};

#endif // EDITCONTROLS_H
