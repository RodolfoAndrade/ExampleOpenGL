#include "heptagon.h"

heptagon::heptagon() :
    // Create vertices along a circle
    pi(2 * acos(0.0)),
    angle(2 * pi / 7),
    angles{ 0, angle, 2 * angle, 3 * angle, 4 * angle, 5 * angle, 6 * angle, 7 * angle },
    vertices{
        0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        sin(angles[0]) / 2, cos(angles[0]) / 2, 0.0f, 1.0f, 0.0f, 0.0f,
        sin(angles[1]) / 2, cos(angles[1]) / 2, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f, 0.647f, 0.0f,
        sin(angles[1]) / 2, cos(angles[1]) / 2, 0.0f, 1.0f, 0.647f, 0.0f,
        sin(angles[2]) / 2, cos(angles[2]) / 2, 0.0f, 1.0f, 0.647f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        sin(angles[2]) / 2, cos(angles[2]) / 2, 0.0f, 1.0f, 1.0f, 0.0f,
        sin(angles[3]) / 2, cos(angles[3]) / 2, 0.0f, 1.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.502f, 0.0f,
        sin(angles[3]) / 2, cos(angles[3]) / 2, 0.0f, 0.0f, 0.502f, 0.0f,
        sin(angles[4]) / 2, cos(angles[4]) / 2, 0.0f, 0.0f, 0.502f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        sin(angles[4]) / 2, cos(angles[4]) / 2, 0.0f, 0.0f, 0.0f, 1.0f,
        sin(angles[5]) / 2, cos(angles[5]) / 2, 0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 0.294f, 0.0f, 0.51f,
        sin(angles[5]) / 2, cos(angles[5]) / 2, 0.0f, 0.294f, 0.0f, 0.51f,
        sin(angles[6]) / 2, cos(angles[6]) / 2, 0.0f, 0.294f, 0.0f, 0.51f,
        0.0f, 0.0f, 0.0f, 0.933f, 0.51f, 0.933f,
        sin(angles[6]) / 2, cos(angles[6]) / 2, 0.0f, 0.933f, 0.51f, 0.933f,
        sin(angles[7]) / 2, cos(angles[7]) / 2, 0.0f, 0.933f, 0.51f, 0.933f
    }
{
}

GLfloat *heptagon::getVertices()
{
    return vertices;
}

size_t heptagon::getSizeOf()
{
    return sizeof(vertices);
}

void heptagon::update()
{
    // Spin the geometry but incrementing the angles
    for (size_t i = 0; i < 8; i++)
    {
        angles[i] = angles[i] + 2 * pi / 1000;
        if (angles[i] > 2 * pi) angles[i] = 0;
    }

    // Replace old position by new ones
    vertices[6 * 1] = sin(angles[0]) / 2;
    vertices[6 * 1 + 1] = cos(angles[0]) / 2;
    vertices[6 * 2] = sin(angles[1]) / 2;
    vertices[6 * 2 + 1] = cos(angles[1]) / 2;
    vertices[6 * 4] = sin(angles[1]) / 2;
    vertices[6 * 4 + 1] = cos(angles[1]) / 2;
    vertices[6 * 5] = sin(angles[2]) / 2;
    vertices[6 * 5 + 1] = cos(angles[2]) / 2;
    vertices[6 * 7] = sin(angles[2]) / 2;
    vertices[6 * 7 + 1] = cos(angles[2]) / 2;
    vertices[6 * 8] = sin(angles[3]) / 2;
    vertices[6 * 8 + 1] = cos(angles[3]) / 2;
    vertices[6 * 10] = sin(angles[3]) / 2;
    vertices[6 * 10 + 1] = cos(angles[3]) / 2;
    vertices[6 * 11] = sin(angles[4]) / 2;
    vertices[6 * 11 + 1] = cos(angles[4]) / 2;
    vertices[6 * 13] = sin(angles[4]) / 2;
    vertices[6 * 13 + 1] = cos(angles[4]) / 2;
    vertices[6 * 14] = sin(angles[5]) / 2;
    vertices[6 * 14 + 1] = cos(angles[5]) / 2;
    vertices[6 * 16] = sin(angles[5]) / 2;
    vertices[6 * 16 + 1] = cos(angles[5]) / 2;
    vertices[6 * 17] = sin(angles[6]) / 2;
    vertices[6 * 17 + 1] = cos(angles[6]) / 2;
    vertices[6 * 19] = sin(angles[6]) / 2;
    vertices[6 * 19 + 1] = cos(angles[6]) / 2;
    vertices[6 * 20] = sin(angles[7]) / 2;
    vertices[6 * 20 + 1] = cos(angles[7]) / 2;
}
