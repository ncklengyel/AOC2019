#include <iostream>
#include <boost/algorithm/string.hpp>
#include <fstream>

enum class Direction : char
{
    RIGHT = 'R',
    LEFT = 'L',
    UP = 'U',
    DOWN = 'D'
};

struct Point2D
{
    int x;
    int y;

    Point2D(int pX, int pY)
    {
        x = pX;
        y = pY;
    }

    bool isEqual(const Point2D& point2D) const
    {
        return (x == point2D.x && y == point2D.y);
    }

    int distance() const
    {
        return std::abs(x) + std::abs(y);
    }
};

std::list<Point2D> createRectLine(const Point2D& from, const int unit, Direction direction)
{
    std::list<Point2D> points;
    switch (direction)
    {
    case Direction::RIGHT:
        for (int i = 1; i < unit+1; i++)
        {
            points.push_back(Point2D(from.x + i, from.y));
        }
        break;
    
    case Direction::LEFT:
        for (int i = 1; i < unit+1; i++)
        {
            points.push_back(Point2D(from.x - i, from.y));
        }
        break;
    
    case Direction::UP:
        for (int i = 1; i < unit+1; i++)
        {
            points.push_back(Point2D(from.x, from.y + i));
        }
        break;

    case Direction::DOWN:
        for (int i = 1; i < unit+1; i++)
        {
            points.push_back(Point2D(from.x, from.y - i));
        }
        break;
    }

    return points;
}

std::list<Point2D> createLine(const std::string& entry, const Point2D& refPoint2D)
{
    std::list<Point2D> line;
    Point2D point(refPoint2D.x, refPoint2D.y);

    int unit = std::stoi(entry.substr(1, entry.size() - 1));
    Direction direction = (Direction)entry.at(0);

    switch (direction)
    {
        case Direction::RIGHT:
            line = createRectLine(point, unit, Direction::RIGHT);
        break;
        case Direction::LEFT:
            line = createRectLine(point, unit, Direction::LEFT);
        break;
        case Direction::UP:
            line = createRectLine(point, unit, Direction::UP);
        break;
        case Direction::DOWN:
            line = createRectLine(point, unit, Direction::DOWN);
        break;

        default:
            std::cout << "Direction not found" << std::endl;
        break;
    }

    return line;
}

std::list<Point2D> getIntersections(const std::list<Point2D>& line1, const std::list<Point2D>& line2)
{
    std::list<Point2D> intersections;
    for(const auto& point1 : line1)
    {
        for (const auto& point2 : line2)
        {
            if(point2.isEqual(point1)) intersections.push_back(point2);
        }
    } 

    return intersections;
}

std::list<Point2D> createWire(const std::list<std::string>& paths)
{
    std::list<Point2D> points;
    Point2D refPoint(0, 0);
    for (const auto& path : paths)
    {
        auto line = createLine(path, refPoint);
        refPoint = line.back();
        points.insert(points.begin(), line.begin(), line.end());
    }

    return points;
}

int getMinDistance(std::list<Point2D> intersections)
{
    int distance = INT_MAX;
    for (const auto& point : intersections)
    {
        int tempDist = point.distance();
        if (tempDist < distance) distance = tempDist;
    }

    return distance;
}


int main()
{
    std::ifstream file("./input.txt");
    std::string line;
    std::list<std::list<std::string>> lines;

    while (std::getline(file, line))
    {
        std::list<std::string> paths;
        boost::split(paths, line, boost::is_any_of(","));
        lines.push_back(paths);
    }

    auto line1 = lines.front();
    lines.pop_front();
    auto line2 = lines.front();
    lines.pop_front();

    auto wire1 = createWire(line1);
    auto wire2 = createWire(line2);

    auto intersections = getIntersections(wire1, wire2);

    int minDistance = getMinDistance(intersections);

    std::cout << "Min distance: " << minDistance << std::endl;

    return 0;
}