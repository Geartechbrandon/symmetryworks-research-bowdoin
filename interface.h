#ifndef INTERFACE_H
#define INTERFACE_H


#include "port.h"

#define MAX_HISTORY_ITEMS 5

const double DEFAULT_WIDTH = 2.5;
const double DEFAULT_HEIGHT = 2.0;
const double DEFAULT_XCORNER = -0.5;
const double DEFAULT_YCORNER = -0.5;
const int DEFAULT_OUTPUT_WIDTH = 6000; //6000 width 4800 height standard for art prints
const int DEFAULT_OUTPUT_HEIGHT = 4800;
const int DEFAULT_PREVIEW_SIZE = 600;

const unsigned int INVALID_FILE_ERROR = 0;



class CustomSpinBox : public QSpinBox
{
  public:
    CustomSpinBox(QWidget *parent = 0) : QSpinBox(parent) { }

  protected:
    void keyPressEvent(QKeyEvent *event) {event->ignore();}

};

class QDoubleSlider : public QSlider
{
    Q_OBJECT
  public:
    QDoubleSlider(QWidget *parent = 0) : QSlider(parent) { 
        connect(this, SIGNAL(valueChanged(int)),
            this, SLOT(notifyValueChanged(int)));
    }

  signals:
    void doubleValueChanged(double value);

  public slots:
    void notifyValueChanged(int value) {
        double doubleValue = value / 100.0;
        emit doubleValueChanged(doubleValue);
    }

};



// class QPopUp : public QMessageBox
// {
//   public: 
//     QPopUp(QObject *parent = 0) : QObject(parent) { }
// };

class interface : public QWidget
{
    Q_OBJECT
public:
    explicit interface(QWidget *parent = 0);
    
    // ORGANIZATIONAL ELEMENTS
    QWidget *functionConstantsWidget;
    QVBoxLayout *interfaceLayout;
    QWidget *displayWidget;
    QHBoxLayout *topbarLayout;
    QVBoxLayout *leftbarLayout;
    QGroupBox *imagePropsBox;
    QWidget *toggleViewWidget;
    QWidget *patternTypeWidget;
    QWidget *viewHistoryWidget;
    QMessageBox *errorMessageBox;

    // INPUT VALIDATORS
    QDoubleValidator *doubleValidate;
    QDoubleValidator *posdoubleValidate;
    QIntValidator *intValidate;
    QIntValidator *posintValidate;
    QIntValidator *numtermsValidate;
    QIntValidator *dimValidate;

    //modeToggle SUBELEMENTS
    QPushButton *toggleViewButton;
    QVBoxLayout *toggleViewLayout;
    
    // functionConstants SUBELEMENTS
    //QScrollArea *functionConstantsScrollArea;
    
    QLabel *currTermLabel;
    CustomSpinBox *currTermEdit;
    QLabel *nLabel;
    QLabel *mLabel;
    QLabel *aLabel;
    QLabel *rLabel;
    // QLabel *nValueLabel;
    // QLabel *mValueLabel;
    QLabel *aValueLabel;
    QLabel *rValueLabel;
    QLabel *scaleALabel;
    QLabel *scaleRLabel;
    // QSlider *nEdit;
    // QSlider *mEdit;

    QSpinBox *nEdit;
    QSpinBox *mEdit;

    QDoubleSlider *aEdit;
    QDoubleSlider *rEdit;
    QPushButton *coeffPlaneEdit;
    
    QWidget *coeffPlanePopUp;
    
    QLabel *globalConsantsLabel;
    QLineEdit *scaleAEdit;
    QLineEdit *scaleREdit;
    QPushButton *scalePlaneEdit;
    
    QWidget *scalePlanePopUp;

    //CustomSpinBox *currTermEdit;

    QGroupBox *functionConstantsBox;
    
    QVBoxLayout *functionConstantsBoxLayout;
    QVBoxLayout *functionConstantsWidgetLayout;
    QHBoxLayout *functionConstantsScalingTerms;
    QHBoxLayout *functionConstantsTerm1;
    QVBoxLayout *functionConstantsPairs;
    QHBoxLayout *functionConstantsFreqs;
    QHBoxLayout *functionConstantsCoeffs;
    
    
//    QHBoxLayout *functionConstantsBoxLayoutLower;
//    QVBoxLayout *functionConstantsBoxLayoutStack;
//    QHBoxLayout *functionConstantsBoxLayoutFirstLevel;
//    QHBoxLayout *functionConstantsBoxLayoutSecondLevel;
//    QHBoxLayout *functionConstantsBoxLayoutThirdLevel;
//    QSpacerItem *espacer1;
//    QSpacerItem *espacer2;
//    QSpacerItem *espacer3;
//    QSpacerItem *espacer4;
//    QSpacerItem *espacer5;
//    QSpacerItem *espacer6;
//    QSpacerItem *espacer7;
    QPushButton *loadButton;
    QPushButton *saveButton;

    // patternTypeBox SUBELEMENTS
    QGroupBox *patternTypeBox;
    QVBoxLayout *patternTypeBoxOverallLayout;
    QVBoxLayout *patternTypeBoxLayout;
    QVBoxLayout *functionLayout;
    QVBoxLayout *colorwheelLayout;
    QHBoxLayout *numtermsLayout;
    QLabel *colorwheelLabel;
    QLabel *functionLabel;
    QLabel *numTermsLabel;
    QLabel *freqpairLabel;
    QLabel *coeffLabel;
    CustomSpinBox *numTermsEdit;
    QSpacerItem *gspacer1;
    QSpacerItem *gspacer2;
    QSpacerItem *gspacer3;
    QSpacerItem *gspacer4;
    QComboBox *colorwheelSel;
    QComboBox *functionSel;
    QPushButton *setLoadedImage;
    
    // viewHistoryBox SUBELEMENTS
    QMap<QDateTime, HistoryItem*> historyItemsMap;
    QGroupBox *viewHistoryBox;
    QVBoxLayout *viewHistoryBoxLayout;
    QVBoxLayout *viewHistoryBoxOverallLayout;
    QPushButton *clearHistoryButton;
    QSignalMapper *viewMapper;
    QSignalMapper *removeMapper;
    

    // imagePropsBox SUBELEMENTS
    QVBoxLayout *imagePropsBoxStack;
    QVBoxLayout *imagePropsEditStack;
    QHBoxLayout *imagePropsBoxLayout;
    QHBoxLayout *savePushLayout;
    QVBoxLayout *imagePropsBoxOverallLayout;
    QLabel *outheightLabel;
    QLabel *outwidthLabel;
    QLabel *XCornerLabel;
    QLabel *YCornerLabel;
    QLabel *worldwidthLabel;
    QLabel *worldheightLabel;
    QLineEdit *outheightEdit;
    QLineEdit *outwidthEdit;
    QLineEdit *XCornerEdit;
    QLineEdit *YCornerEdit;
    QLineEdit *worldwidthEdit;
    QLineEdit *worldheightEdit;
    QSpacerItem *pspacer1;
    QSpacerItem *pspacer2;
    QSpacerItem *pspacer3;
    QSpacerItem *pspacer4;
    QSpacerItem *pspacer5;

    // DISP SUBELEMENTS
    QPushButton *updatePreview;
    QPushButton *exportImage;
    QPushButton *resetImage;
    Display *disp;
    QVBoxLayout *dispLayout;
    QHBoxLayout *buttonLayout;

    // SHORTCUTS
    QShortcut *updatePreviewShortcut;

private slots:
    void toggleViewMode();
    void updateTerms(int i);
    void changeMaxTerms(int i);
    void colorWheelChanged(int index);
    void setImagePushed();
    void changeFunction(int index);
    void changeWorldWidth(const QString &val);
    void changeWorldHeight(const QString &val);
    void changeXCorner(const QString &val);
    void changeYCorner(const QString &val);
    void changeOWidth(const QString &val);
    void changeOHeight(const QString &val);
    void changeN(int val);
    void changeM(int val);
    void changeR(double val);
    void changeA(double val);
    void changeScaleR(const QString &val);
    void changeScaleA(const QString &val);
    void saveImageStart();
    void resetImageFunction();
    void removePreview(QObject *item);
    void loadFromSettings();
    void saveCurrSettings();
    void updateSavePreview();
    void clearAllHistory();

    void showPlanePopUp();
    
    QString loadSettings(const QString &fileName);
    
private:    
    QString genLabel(const char * in);    
    QString getCurrSettings(const HistoryItem &item);
    QString saveSettings(const QString &fileName);

    void refreshLabels();
    void updatePreviewDisplay();
    void addToHistory();
    void errorHandler(const int &flag);    
    void refreshTerms();

    unsigned int termIndex;  //internal index:  starts at 0 
    QString saveloadPath;
    AbstractFunction * currFunction;
    ColorWheel * currColorWheel;
    bool advancedMode;
    
};

#endif // INTERFACE_H
