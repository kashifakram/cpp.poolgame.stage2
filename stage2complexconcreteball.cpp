#include "stage2complexconcreteball.h"

extern bool showNestedBall;

Stage2ComplexConcreteBall::Stage2ComplexConcreteBall(
        const QColor& color,
        const float strength,
        bool isCueBall,
        float radius,
        float mass,
        const QVector2D& pos,
        const QVector2D& vel
):Ball(radius, mass, pos, vel), m_color(color), m_strength(strength), m_isCueBall(isCueBall) {}

void Stage2ComplexConcreteBall::draw(QPainter& painter, QVector2D offset) const {
    QBrush brush(this->m_color);
    painter.setBrush(brush);
    painter.drawEllipse(
        (this->position + offset).toPointF(),
        this->radius, this->radius
    );
    if(showNestedBall){
        for (const auto & b : m_balls){
            b->draw(painter, position + offset);
        }
    }
}

std::vector<std::unique_ptr<Ball>> *Stage2ComplexConcreteBall::manageBallCollision(const QVector2D& inputDeltaV)
{
    float ballMass=mass;
    float ballStrength=getStrength();
    float ballRadius=radius;
    QVector2D preCollisionVelocity=velocity;
    QVector2D deltaV=inputDeltaV;
    float energyOfCollision = ballMass*deltaV.lengthSquared();
    if(ballStrength>0 && ballStrength<energyOfCollision)
    {
        int numComponentBalls=getNumberOfChildBalls();
        float energyPerBall = energyOfCollision/numComponentBalls;
        QVector2D pointOfCollision((-deltaV.normalized())*ballRadius);

        for(const auto & b : m_balls)
        {
            float componentBallMass=b->mass;
            QVector2D componentBallPosition = b->position;
            QVector2D componentBallVelocity = preCollisionVelocity + sqrt(energyPerBall/componentBallMass)*(componentBallPosition-pointOfCollision).normalized();
            b->position = componentBallPosition+this->position;
            b->velocity = componentBallVelocity;
        }

        setIsDestroyed();
        return getChildren();
    }
    else
    {
        velocity += inputDeltaV;
    }
    return nullptr;

}

bool Stage2ComplexConcreteBall::getIsDestroyed(){return m_isDestroyed;}
void Stage2ComplexConcreteBall::setIsDestroyed(){m_isDestroyed = !m_isDestroyed;}

std::vector<std::unique_ptr<Ball> > *Stage2ComplexConcreteBall::getChildren(){
    return &m_balls;
}


bool Stage2ComplexConcreteBall::isCueBall()
{
    return m_isCueBall;
}

void Stage2ComplexConcreteBall::setCueBall()
{
    m_isCueBall = true;
}

void Stage2ComplexConcreteBall::addBalls(unique_ptr<Ball> ball)
{
    m_balls.emplace_back(std::move(ball));

}

float Stage2ComplexConcreteBall::getStrength(){
    return m_strength;
}

QColor Stage2ComplexConcreteBall::getBallColor(){
    return m_color;
}

float Stage2ComplexConcreteBall::getCombinedMass(){
    float mass = 0;
    for(auto &b : m_balls){
        mass += b->mass;
    }
    return mass;
}

int Stage2ComplexConcreteBall::getNumberOfChildBalls(){
    float totalChilds = 0;
    for(auto &b : m_balls){
        totalChilds += 1;
    }
    return totalChilds;
}

float Stage2ComplexConcreteBall::getRadius(){
    return radius;
}

QVector2D Stage2ComplexConcreteBall::getPosition(){
    return position;
}

QVector2D Stage2ComplexConcreteBall::getVelocity()
{
    return velocity;
}
