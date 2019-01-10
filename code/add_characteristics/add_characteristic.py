import numpy as np
from numpy import genfromtxt


def splitGlobalTrajectory(globalPoints, stepSize):
        # Up
    length = np.linalg.norm(globalPoints[0] - globalPoints[1])
    numberOfIncrements = int(length/stepSize)

    x = np.linspace(globalPoints[0, 0],
                    globalPoints[1, 0], numberOfIncrements+1)
    y = np.linspace(globalPoints[0, 1],
                    globalPoints[1, 1], numberOfIncrements+1)
    z = np.linspace(globalPoints[0, 2],
                    globalPoints[1, 2], numberOfIncrements+1)

    # Straight
    length = np.linalg.norm(globalPoints[1] - globalPoints[2])
    numberOfIncrements = int(length/stepSize)

    x = np.append(x, np.linspace(globalPoints[1, 0],
                                 globalPoints[2, 0], numberOfIncrements+1))
    y = np.append(y, np.linspace(globalPoints[1, 1],
                                 globalPoints[2, 1], numberOfIncrements+1))
    z = np.append(z, np.linspace(globalPoints[1, 2],
                                 globalPoints[2, 2], numberOfIncrements+1))

    # Down
    length = np.linalg.norm(globalPoints[2] - globalPoints[3])
    numberOfIncrements = int(length/stepSize)

    x = np.append(x, np.linspace(globalPoints[2, 0],
                                 globalPoints[3, 0], numberOfIncrements+1))
    y = np.append(y, np.linspace(globalPoints[2, 1],
                                 globalPoints[3, 1], numberOfIncrements+1))
    z = np.append(z, np.linspace(globalPoints[2, 2],
                                 globalPoints[3, 2], numberOfIncrements+1))

    return np.matrix([x, y, z]).T


def addCharacteristics(steps, flyingCharacteristics, characterGain, everyXth):
    speed = False
    counter = 0
    frames = flyingCharacteristics.shape[0]
    newSteps = []
    previousPoint = 0
    while (counter*frames < steps.shape[0]):
        for i in range(frames):
            if (counter*frames + i < steps.shape[0]):
                newPoint = steps[counter*frames + i] + \
                    characterGain * flyingCharacteristics[i]
                if (speed and counter*frames + i != 0 and (counter*frames+i) % everyXth == 0):
                    newSteps.append(newPoint - previousPoint)
                elif not speed:
                    newSteps.append(newPoint)
                previousPoint = newPoint
        counter += 1
    return np.vstack(newSteps)


if __name__ == "__main__":
    # Init parameters.
    filename = 'data/input/Lost.csv'
    stepSize = 0.03
    characterGain = 0.000
    everyXth = 1

    # Create global trajectory points.
    globalPoints = np.matrix([
        [0.0, 0.0, 1.0],
        [0.0, 0.0, 5.0],
        [10.0, 0.0, 5.0],
        [10.0, 0.0, 2.0]])

    # Read flying characteristics.
    flyingCharacteristics = genfromtxt(filename, delimiter=';')

    # Split global trajectory according to step size.
    steps = splitGlobalTrajectory(globalPoints, stepSize)

    # Add flying characteristics to steps.
    newSteps = addCharacteristics(
        steps, flyingCharacteristics, characterGain, everyXth)

    # Save matrix to txt file.
    np.savetxt('data/matlab/Original.txt', newSteps)
