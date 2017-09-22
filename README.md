# Background

A river flows from north to south. There are cities on the west bank and
cities on the east bank. We wish to build bridges across the river. Each
bridge will join a west-bank city with an east-bank city. We wish to choose
the bridges we build in such a way as to maximize the tolls we collect from
people crossing them.

There are two restrictions on the bridges we build. First, no city can have
more than one bridge reaching it. Second, no two bridges can cross each
other.

Concerning the second condition: the cities on each bank are numbered.
There are w cities on the west bank, numbered 0, 1, …, w-1 (starting at
zero, because we’re computer scientists), and there are e cities on the east
bank, numbered 0, 1, …, e-1. Suppose one bridge joins city a on the west to
city b on the east. Another bridge joins city c on the west to city d on the
east. If a<c and b>d, then these two bridges cross each other, and we are
not allowed to build both.

For each pair of cities we might build a bridge between, we know the toll we
will collect from it. Building a bridge never affects the toll collected from
another bridge.