#include "scenemanager.h"
#include "math.h"

//void collideBalls(Ball&, Ball&);
//void collideTable(const Table&, Ball&);
//QVector2D isTouching(const Ball&, const Ball&);
//QVector2D isTouching(const Table&, const Ball&);

SceneManager::SceneManager(unique_ptr<Table> poolTable, vector<unique_ptr<Ball>>& initBalls)
: table(std::move(poolTable)), balls(std::move(initBalls)), offset(20, 20) {}

void SceneManager::draw(QPainter& painter, QVector2D) const {
	painter.translate(offset);
	this->table->draw(painter);

	for (const auto& item: this->balls) {
        item->draw(painter);
	}
	painter.translate(-offset);
}

QSize SceneManager::veiwPort() const {
	return this->table->dimension + QSize(this->offset.x(), this->offset.y())*2;
}

void SceneManager::tick(float dtime) {

	for (auto a = this->balls.begin(); a != this->balls.end(); ++a) {
		Ball& ballA = **a;
		collideTable(*this->table, ballA);
		for (auto b = a + 1; b != this->balls.end(); ++b) {
			collideBalls(ballA, **b);
		}

		ballA.position += ballA.velocity * dtime;
		ballA.velocity -= ballA.velocity.normalized() * dtime * this->table->surface_friction;
	}
}

void collideTable(const Table& table, Ball& ball) {

	auto collision = isTouching(table, ball);

	if (QVector2D::dotProduct(collision, ball.velocity) < 0)
		return;

	if (collision.x())
		ball.velocity *= QVector2D(-1, 1);
	else if (collision.y())
		ball.velocity *= QVector2D(1, -1);
}

void collideBalls(Ball& ballA, Ball& ballB) {
	// SOURCE : ASSIGNMENT SPEC
	auto collision = isTouching(ballA, ballB);
	if (collision == NULL_2D) return;

	float mr = ballB.mass / ballA.mass;
	double pa = QVector2D::dotProduct(collision, ballA.velocity);
	double pb = QVector2D::dotProduct(collision, ballB.velocity);

	if (pa <= 0 && pb >= 0) return;

	double a = -(mr + 1);
	double b = 2*(mr * pb + pa);
	double c = -((mr - 1)*pb*pb + 2*pa*pb);
	double disc = sqrt(b*b - 4*a*c);
	double root = (-b + disc)/(2*a);
	if (root - pb < 0.01) {
		root = (-b - disc)/(2*a);
	}

	ballA.velocity += mr * (pb - root) * collision;
	ballB.velocity += (root - pb) * collision;
}

QVector2D isTouching(const Ball& ballA, const Ball& ballB) {
	auto collision = ballB.position - ballA.position;
	if (collision.length() <= ballA.radius + ballB.radius)
		return collision.normalized();
	else
		return NULL_2D;
}

QVector2D isTouching(const Table& table, const Ball& ball) {
	if (ball.position.x() <= ball.radius)
		return QVector2D(-1, 0);
	else if (ball.position.y() <= ball.radius)
		return QVector2D(0, -1);
	else if (ball.position.x() + ball.radius >= table.dimension.width())
		return QVector2D(1, 0);
	else if (ball.position.y() + ball.radius >= table.dimension.height())
		return QVector2D(0, 1);
	else
		return NULL_2D;
}
