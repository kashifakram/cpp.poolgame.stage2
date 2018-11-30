#include "stage2engine.h"
#include "stage2complexconcreteball.h"
#include "stage2complexconcretetable.h"
#include "pocket.h"
#include "math.h"

#include <iterator>

//void collideBalls(Ball&, Ball&);
//void collideTable(const Table&, Ball&);
//QVector2D isTouching(const Ball&, const Ball&);
//QVector2D isTouching(const Table&, const Ball&);

extern bool showNestedBall;

Stage2Engine::Stage2Engine(std::unique_ptr<Table> poolTable, vector<std::unique_ptr<Ball>> initBalls)
    : m_table(std::move(poolTable)), m_balls(std::move(initBalls)), m_mousePos()
    , m_tempBalls(), m_timer(), m_clickPower(0), m_clicked(false)
    , m_showIndicators(false) {
//    qDebug() << "num of balls" << m_balls.size();
    for(const auto &b : m_balls){
        qDebug() << b->isCueBall();
    }
}

//Stage2Engine::~Stage2Engine() {}

void Stage2Engine::draw(QPainter& painter, QVector2D) const {
    painter.translate(m_offset);
    this->m_table->draw(painter);
//        qDebug() << "num of balls" << m_balls.size();
    for(const auto & item: this->m_balls) {
//        qDebug() << "calling draw";
        item->draw(painter);
    }

    painter.translate(-m_offset);


    painter.setPen(Qt::green);//draw the power rectangle
    painter.setBrush(QBrush(Qt::blue));
    painter.drawRect(0, m_table->dimension.height()+40, m_clickPower*(m_table->dimension.width())/2+2, 60);

    painter.setPen(Qt::white);//draw a line to show hitting direction
    painter.setBrush(QBrush(Qt::white));

    for(const auto & b : m_balls)
    {
        if(b->isCueBall() && (!m_mousePos.isNull())&& m_clicked && b->velocity.isNull())
        {
            float x = b->position.x();
            float y = b->position.y();
            painter.drawLine(m_mousePos.x(), m_mousePos.y(), 2*x-m_mousePos.x(), 2*y-m_mousePos.y());
        }
    }

}


void Stage2Engine::tick(float dtime) {

//    for(size_t i = 0; i < m_balls.size(); ++i){
//        qDebug() << "Ball" << i << "speed" << m_balls[i]->velocity.length();
//    }

    if (m_timer.isValid())
    {
        auto t = m_timer.elapsed();
        m_clickPower = (t%1000) / 500.0;
    }


    for (const auto & b : m_balls)
    {
//        Ball *ball = b->get();
        if(!b->getIsDestroyed())
        {
            BallInPocket(m_table.get(), b.get());
            if (!b->getIsDestroyed())
            {
                BallToTableCollision(m_table.get(), b.get());
            }

        }
    }

    //a collision between each possible pair of balls

    for (auto j = 0; j < m_balls.size(); ++j) {
        for(int k = j+1; k < m_balls.size();++k)
        {
            if((!m_balls[j]->getIsDestroyed())&&(!m_balls[k]->getIsDestroyed()))
            {
                BallToBallCollision(m_balls[j].get(),m_balls[k].get());
            }
        }
    }

    //removing balls which are broken
    for (auto b = m_balls.begin(); b != this->m_balls.end();) {
        const auto &ball = *b;

        if (ball->getIsDestroyed()){
            b = m_balls.erase(b);
        } else {
            b++;
        }
    }

    //adding temporary balls as child balls
    m_balls.insert(m_balls.end(),std::make_move_iterator(m_tempBalls.begin()), std::make_move_iterator(m_tempBalls.end()));
    m_tempBalls.clear();

    for (const auto & b : m_balls) {
        b->position += b->velocity * dtime;
        b->velocity -= b->velocity.normalized() * dtime * this->m_table->surface_friction;

        if (b->velocity.length() < 3)
        {
            b->velocity = NULL_2D;
        }
    }

//    for (auto ball = this->m_balls.begin(); ball != this->m_balls.end(); ball++){
//        if ((*ball)->getIsDestroyed()){
//           ball = m_balls.erase(ball);
//               ball = m_balls.emplace_back(std::move(ball));
//        }
//        else {
//            ball++;
//        }
//    }

}


void Stage2Engine::BallInPocket(Table *table, Ball *ball)
{
    const vector<std::unique_ptr<Pocket>>* pockets = table->getPockets();
//if there are pockets on table
    if (pockets)
    {
        for (const std::unique_ptr<Pocket> &p : *pockets)
        {
            if (QVector2D(ball->position-p->GetPosition()).length() <= p->GetRadius())
            {
                ball->setIsDestroyed();
                break;
            }
        }
    }
}

QSize Stage2Engine::size(){
    return m_table->dimension + QSize(0, 100);
}

Ball * Stage2Engine::findCueBall(){
//    Ball * result = nullptr;
    for (const auto &b : m_balls){
        Stage2ComplexConcreteBall * S2Ball = dynamic_cast<Stage2ComplexConcreteBall*>(b.get());
        if (S2Ball->isCueBall())
            return b.get();
    }
    return nullptr;
//    return result;
}

void Stage2Engine::setIsClicked(bool clicked)
{
    m_clicked = clicked;
}

void Stage2Engine::pushCueueBall()
{
    for (const auto & b : m_balls)
    {
        Stage2ComplexConcreteBall * S2Ball = dynamic_cast<Stage2ComplexConcreteBall*>(b.get());
        if(S2Ball->isCueBall() && S2Ball->getVelocity().isNull())
        {
            b->velocity = (-(m_mousePos-b->position)*m_clickPower*10);
        }
    }
}


void Stage2Engine::mousePressEvent(QMouseEvent * event) {
    if(findCueBall() && findCueBall()->velocity.isNull()){
        if(!m_timer.isValid()){
            m_timer.start();
        }
        m_clicked = true;
    }
}

void Stage2Engine::mouseReleaseEvent(QMouseEvent *){
    if (m_timer.isValid() && m_clicked)
    {
        Ball *cueball = findCueBall();
        cueball->velocity += (m_mousePos - cueball->position).normalized() * m_clickPower * 200;
        m_clicked = false;
        m_clickPower = 0;
        m_mousePos = NULL_2D;
        m_timer.invalidate();
    }
}

void Stage2Engine::mouseMoveEvent(QMouseEvent *event){
    if(m_timer.isValid() && m_clicked)
        m_mousePos = QVector2D(event->pos());
}

void Stage2Engine::BallToBallCollision(Ball *ballA, Ball *ballB)
{
    if(ballA == nullptr || ballB == nullptr)
        return;

    //checking the distance between their centers
    if ((ballA->position - ballB->position).length()  < (ballA->radius + ballB->radius))
    {
        //using the code provided for the collision mechanics

         //calculate their mass ratio
         float mR = ballB->mass / ballA->mass;

         //calculate the axis of collision
         QVector2D collisionVector = ballB->position - ballA->position;
         collisionVector.normalize();

        //the proportion of each balls velocity along the axis of collision
         double vA = QVector2D::dotProduct(collisionVector, ballA->velocity);
         double vB = QVector2D::dotProduct(collisionVector, ballB->velocity);
         //the balls are moving away from each other so do nothing
         if (vA <= 0 && vB >= 0) {
          return;
         }

         //The velocity of each ball after a collision can be found by solving the quadratic equation
         //given by equating momentum and energy before and after the collision and finding the velocities
         //that satisfy this
         //-(mR+1)x^2 2*(mR*vB+vA)x -((mR-1)*vB^2+2*vA*vB)=0
         //first we find the discriminant
         double a = -(mR + 1);
         double b = 2 * (mR * vB + vA);
         double c = -((mR - 1) * vB * vB + 2 * vA * vB);
         double discriminant = sqrt(b * b - 4 * a * c);
         double root = (-b + discriminant)/(2 * a);
         //only one of the roots is the solution, the other pertains to the current velocities
         if (root - vB < 0.01) {
           root = (-b - discriminant)/(2 * a);
         }

         qDebug() << "Pre vel" << ballA->velocity.length();
         //The resulting changes in velocity for ball A and B
         auto newBallsFrom1=ballA->manageBallCollision(mR * (vB - root) * collisionVector);
         auto newBallsFrom2=ballB->manageBallCollision((root - vB) * collisionVector);
         if(newBallsFrom1)
             m_tempBalls.insert(m_tempBalls.end(), std::make_move_iterator(newBallsFrom1->begin()),std::make_move_iterator(newBallsFrom1->end()));
         if(newBallsFrom2)
             m_tempBalls.insert(m_tempBalls.end(), std::make_move_iterator(newBallsFrom2->begin()),std::make_move_iterator(newBallsFrom2->end()));

         qDebug() << "Post vel" << ballA->velocity.length();
    }

}


void Stage2Engine::BallToTableCollision(Table *table, Ball *ball)
{
    if(ball == nullptr)
        return;

    // collision happend on left or right side of table

    if((ball->position.x()<ball->radius && ball->velocity.x()<0) || (ball->position.x()>table->dimension.width()-ball->radius && ball->velocity.x() > 0))
    {
        vector<std::unique_ptr<Ball>> *newBalls=ball->manageBallCollision(QVector2D(-ball->velocity.x()*2,0));
        if(newBalls)
            m_tempBalls.insert(m_tempBalls.end(),std::make_move_iterator(newBalls->begin()),std::make_move_iterator(newBalls->end()));
    }

    if((ball->position.y()<ball->radius && ball->velocity.y() < 0) || (ball->position.y() > table->dimension.height()-ball->radius && ball->velocity.y() > 0))
    {
        vector<std::unique_ptr<Ball>> *newBalls=ball->manageBallCollision(QVector2D(0, -ball->velocity.y()*2));
        if(newBalls)
            m_tempBalls.insert(m_tempBalls.end(),std::make_move_iterator(newBalls->begin()),std::make_move_iterator(newBalls->end()));
    }

}


void Stage2Engine::CalculateFriction(Ball *ball, double friction, qint64 prevTime, qint64 currTime)
{
    Stage2ComplexConcreteBall * S2Ball =  dynamic_cast<Stage2ComplexConcreteBall *>(ball);
    auto changeInXVelocity = S2Ball->getVelocity().x() * (1-friction * ((currTime - prevTime))/1000  );
    auto changeInYVelocity = S2Ball->getVelocity().y() * (1-friction * ((currTime - prevTime))/1000 );


    S2Ball->velocity = QVector2D(changeInXVelocity, changeInYVelocity);
}


bool Stage2Engine::WereBallsCollided(Ball *ballA, Ball *ballB)
{
    if(GetDistanceBetweenPositions(ballA->position, ballB->position) <= (ballA->radius + ballB->radius))
        return true;

    return false;
}

double Stage2Engine::GetDistanceBetweenPositions(QVector2D positionA, QVector2D positionB)
{
    double distance = 0;
    double deltaX = positionA.x() - positionB.x();
    double deltaY = positionA.y() - positionB.y();
    distance = sqrt((deltaX*deltaX) + (deltaY*deltaY));
    return distance;
}

bool Stage2Engine::IsGameFinished()
{
    if (!m_table || m_balls.empty())
        return true;

    return false;
}
