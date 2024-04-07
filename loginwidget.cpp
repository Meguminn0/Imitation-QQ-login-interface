#include <QMouseEvent>
#include <QAction>
#include <QGraphicsDropShadowEffect>
#include <QPainterPath>
#include <QWindow>
#include <QLabel>


#include "headlabel.h"
#include "loginwidget.h"
#include "ui_loginwidget.h"

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    m_readyMove = false;

    ui->label_QRCode->installEventFilter(this);
    ui->comboBox_userName->installEventFilter(this);
    ui->lineEdit_pwd->installEventFilter(this);

    setWindowFlags(Qt::FramelessWindowHint);

    setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(10);
    shadowEffect->setColor(QColor(0, 0, 0, 128));
    shadowEffect->setOffset(0, 0);
    ui->widget_shadow->setGraphicsEffect(shadowEffect);

    this->init();
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::init()
{
    QPalette palette;

    // LOGO
    QLabel *logoLabel = new QLabel(this);
    QPixmap logoPixmap(":/icon/qq_logo.png");
    logoLabel->setPixmap(logoPixmap);
    logoLabel->setGeometry(15, 15, 58, 29);
    logoLabel->setScaledContents(true);

    // set setBtn, minBtn, closeBtn icon
    ui->Btn_close->setAutoFillBackground(true);
    ui->Btn_close->setFlat(true);
    palette = ui->Btn_close->palette();
    palette.setColor(QPalette::Button, Qt::transparent);
    ui->Btn_close->setPalette(palette);
    ui->Btn_close->setIcon(QPixmap(":/icon/whiteClose.png"));
    ui->Btn_close->setIconSize(QSize(14, 14));
    ui->Btn_close->setStyleSheet(R"(
        QPushButton { border: none; background-color: transparent; }
        QPushButton:hover { background-color: rgb(255,84,57) }
        QPushButton:pressed { background-color: rgb(224,74,50); border-style: outset; }
    )");

    ui->Btn_min->setAutoFillBackground(true);
    ui->Btn_min->setFlat(true);
    palette = ui->Btn_min->palette();
    palette.setColor(QPalette::Button, Qt::transparent);
    ui->Btn_min->setPalette(palette);
    ui->Btn_min->setIcon(QPixmap(":/icon/whiteMin.png"));
    ui->Btn_min->setIconSize(QSize(17, 17));
    ui->Btn_min->setStyleSheet(R"(
        QPushButton { border: none; background-color: transparent; }
        QPushButton:hover { background-color: rgba(255, 255, 255, 50) }
        QPushButton:pressed { background-color: rgba(255, 255, 255, 100); border-style: outset; }
    )");

    ui->Btn_set->setAutoFillBackground(true);
    ui->Btn_set->setFlat(true);
    palette = ui->Btn_set->palette();
    palette.setColor(QPalette::Button, Qt::transparent);
    ui->Btn_set->setPalette(palette);
    ui->Btn_set->setIcon(QPixmap(":/icon/whiteSetting.png"));
    ui->Btn_set->setIconSize(QSize(16, 16));
    ui->Btn_set->setStyleSheet(R"(
        QPushButton { border: none; background-color: transparent; }
        QPushButton:hover { background-color: rgba(255, 255, 255, 50) }
        QPushButton:pressed { background-color: rgba(255, 255, 255, 100); border-style: outset; }
    )");

    // set topPicture
    ui->label_TopPicture->setAutoFillBackground(true);
    palette = ui->label_TopPicture->palette();
    palette.setColor(QPalette::Window, QColor(25,200,254));
    ui->label_TopPicture->setPalette(palette);

    // set widget_down
    ui->widget_down->setAutoFillBackground(true);
    palette = ui->widget_down->palette();
    palette.setColor(QPalette::Window, Qt::white);
    ui->widget_down->setPalette(palette);

    // set head Label
    QPixmap headPixmap(":/head1.png");
    headLabel *head = new headLabel(ui->widget_shadow);
    head->setGeometry(170, 88, 65, 65);
    head->setPixmap(headPixmap);
    QGraphicsDropShadowEffect *headShadowEffect = new QGraphicsDropShadowEffect(this);
    headShadowEffect->setBlurRadius(50);
    headShadowEffect->setColor(QColor(69,134,247));
    headShadowEffect->setOffset(0, 0);
    head->setGraphicsEffect(headShadowEffect);

    // set loginBtn
    ui->Btn_login->setStyleSheet(R"(
        QPushButton { border: none; background-color: rgb(4,186,251); color: white; font: 14px; }
        QPushButton:hover { background-color: rgb(29,197,252) }
    )");
    QGraphicsDropShadowEffect *loginShadowEffect = new QGraphicsDropShadowEffect(this);
    loginShadowEffect->setBlurRadius(10);
    loginShadowEffect->setColor(QColor(29,197,252, 128));
    loginShadowEffect->setOffset(0, 0);
    ui->Btn_login->setGraphicsEffect(loginShadowEffect);

    // set checkBox and label
    ui->checkBox_autoLogin->setStyleSheet("QCheckBox{color: rgb(184,186,188)}");
    ui->checkBox_rememberPwd->setStyleSheet("QCheckBox{color: rgb(184,186,188)}");
    ui->label_retrievePwd->setStyleSheet(R"(
        QLabel{color: rgb(184,186,188)}
        QLabel:hover{ color: rgb(146,149,152) }
    )");

    // set userName and password LineEdit
    ui->comboBox_userName->setEditable(true);
    QAction *userAction = new QAction(this);
    userAction->setIcon(QIcon(":/icon/userNameQQLogo.png"));
    ui->comboBox_userName->lineEdit()->addAction(userAction, QLineEdit::LeadingPosition);
    ui->comboBox_userName->lineEdit()->setPlaceholderText("QQ号码/手机/邮箱");
    ui->comboBox_userName->setStyleSheet(R"(
        QComboBox{ border: none; border-bottom: 1px solid rgb(184,186,188); }
        QComboBox::drop-down{ width: 20px; height: 20px; border-image: url(:/icon/grenDownArrows.png); }
        QComboBox::drop-down:hover{ width: 20px; height: 20px; border-image: url(:/icon/deepGrenDownArrows.png); }
        QComboBox::drop-down:checked{ width: 20px; height: 20px; border-image: url(:/icon/deepGrenUpArrows.png); }
        QComboBox:hover { border-bottom: 1px solid rgb(146,149,152); }
        QComboBox:focus { border-bottom: 1px solid rgb(18,183,245);) }
    )");

    QAction *pwdAction = new QAction(this);
    pwdAction->setIcon(QIcon(":/icon/grenLock.png"));
    ui->lineEdit_pwd->addAction(pwdAction, QLineEdit::LeadingPosition);
    ui->lineEdit_pwd->setPlaceholderText("QQ密码");
    ui->lineEdit_pwd->setStyleSheet(R"(
        QLineEdit{ border: none; border-bottom: 1px solid rgb(184,186,188); }
        QLineEdit:hover { border-bottom: 1px solid rgb(146,149,152); }
        QLineEdit:focus { border-bottom: 1px solid rgb(18,183,245); }
    )");

    // set register ander QRCode label
    ui->label_register->setStyleSheet(R"(
        QLabel{ color: rgb(184,186,188); }
        QLabel:hover{ color: rgb(146,149,152); }
    )");

    QPixmap QRCodePixmap(":/icon/grenQRCode.png");
    ui->label_QRCode->setScaledContents(true);
    ui->label_QRCode->setPixmap(QRCodePixmap);
}

bool LoginWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::Leave && watched == ui->label_QRCode)
    {
        QPixmap QRCodePixmap(":/icon/grenQRCode.png");
        ui->label_QRCode->setPixmap(QRCodePixmap);
        return true;
    }
    else if(event->type() == QEvent::Enter && watched == ui->label_QRCode)
    {
        QPixmap QRCodeHoverPixmap(":/icon/deepGrenQRCode.png");
        ui->label_QRCode->setPixmap(QRCodeHoverPixmap);
        return true;
    }
    else if(event->type() == QEvent::FocusAboutToChange && watched == ui->comboBox_userName)
    {
        QList<QAction*> allActions = ui->comboBox_userName->lineEdit()->actions();
        if(allActions.isEmpty())
            return true;
        allActions.first()->setIcon(QIcon(":/icon/userNameQQLogo.png"));
    }
    else if(event->type() == QEvent::FocusIn && watched == ui->comboBox_userName)
    {
        QList<QAction*> allActions = ui->comboBox_userName->lineEdit()->actions();
        if(allActions.isEmpty())
            return true;
        allActions.first()->setIcon(QIcon(":/icon/userNameQQLogo_checked.png"));
    }
    else if(event->type() == QEvent::FocusAboutToChange && watched == ui->lineEdit_pwd)
    {
        QList<QAction*> allActions = ui->lineEdit_pwd->actions();
        if(allActions.isEmpty())
            return true;
        allActions.first()->setIcon(QIcon(":/icon/grenLock.png"));
    }
    else if(event->type() == QEvent::FocusIn && watched == ui->lineEdit_pwd)
    {
        QList<QAction*> allActions = ui->lineEdit_pwd->actions();
        if(allActions.isEmpty())
            return true;
        allActions.first()->setIcon(QIcon(":/icon/openLock.png"));
    }
    else if(event->type() == QEvent::None)
    {
        QWidget::eventFilter(watched, event);
    }
}

void LoginWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        // 鼠标在登录窗口中按下了左键,准备开始移动
        m_readyMove = true;
        // 记录当前窗口和鼠标的位置
        m_currentPos = frameGeometry().topLeft();
        m_mouseStartPoint = event->globalPos();
    }
}

void LoginWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_readyMove)
    {
        QPoint moveDistance = event->globalPos() - m_mouseStartPoint;
        move(m_currentPos + moveDistance);
    }
}

void LoginWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_readyMove = false;
    }
}

void LoginWidget::on_Btn_min_clicked()
{
    this->showMinimized();
}

void LoginWidget::on_Btn_close_clicked()
{
    this->close();
}
