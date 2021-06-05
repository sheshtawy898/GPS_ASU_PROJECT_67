#include <stdio.h>
#include<math.h>

      // CONVERTING TO RADIANS //
 double degreesToRadians (double degrees)
{ double pi =3.14;
  return degrees * pi / 180;
}

  // GETTING DISTANCE BETWEEN TWO COORDINATES //
 double distanceCoordinates (double lat1, double lon1, double lat2, double lon2)
{
  double earthRadiusKm = 6371;

  double dLat = degreesToRadians (lat2 - lat1);
  double dLon = degreesToRadians (lon2 - lon1);

  lat1 = degreesToRadians (lat1);
  lat2 = degreesToRadians (lat2);

  double a = sin (dLat / 2) * sin (dLat / 2) +
    sin (dLon / 2) * sin (dLon / 2) * cos (lat1) *
    cos (lat2);
  double c = 2 * atan2 (sqrt (a), sqrt (1 - a));
  return earthRadiusKm * c*1000;
}

  //TESTING THE TWO FUNCTIONS//
int main(){
    double y;
    y = distanceCoordinates(30.06422,31.27989,30.06372,31.28013);
    printf("%lf",y);

}
