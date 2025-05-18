#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Range {
    int starting, ending;
};

struct Camera {
    Range distance;
    Range light;
};

sortRangeCondition(Range a, Range b) {
    return a.starting < b.starting;
}

bool isRangeCovered(vector<Range> ranges, Range desired) {
    sort(ranges.begin(), ranges.end(), sortRangeCondition);

    int current = desired.starting;
    for (int i=0;i<ranges.size();i++) {
        if (ranges[i].starting > current) return false;
        current = max(current, ranges[i].ending);
        if (current >= desired.ending) return true;
    }
    return current >= desired.ending;
}

bool canSoftwareCameraBeBuilt(Range desiredDistance, Range desiredLight, vector<Camera> cameras) {
    vector<Range> distanceRanges, lightRanges;
    for (int i=0;i<cameras.size();i++) {
        distanceRanges.push_back(cameras[i].distance);
        lightRanges.push_back(cameras[i].light);
    }
    return isRangeCovered(distanceRanges, desiredDistance) && isRangeCovered(lightRanges, desiredLight);
}


int main() {
    Range desiredDistance = {1, 10};
    Range desiredLight = {100, 400};

    vector<Camera> cameras = {
        {{1, 4}, {100, 200}},
        {{4, 7}, {150, 300}},
        {{7, 10}, {200, 400}}
    };

    if (canSoftwareCameraBeBuilt(desiredDistance, desiredLight, cameras)) {
        cout << "Yes, the hardware cameras can cover the desired ranges.\n";
    } else {
        cout << "No, the hardware cameras cannot cover the desired ranges.\n";
    }

    return 0;
}
