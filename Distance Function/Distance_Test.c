#include <stdio.h>
#include<math.h>
#define PI 3.14159
double dLat;
double dLon;
double a;
double c;
      // CONVERTING TO RADIANS //
 double degreesToRadians (double degrees)
{ 
  return degrees * PI / 180;
}

  // GETTING DISTANCE BETWEEN TWO COORDINATES //
 double distanceCoordinates (double lat1, double lon1, double lat2, double lon2)
{
  double earthRadiusKm = 6371;

  dLat = degreesToRadians (lat2 - lat1);
  dLon = degreesToRadians (lon2 - lon1);

  lat1 = degreesToRadians (lat1);
  lat2 = degreesToRadians (lat2);

   a = sin (dLat / 2) * sin (dLat / 2) +
    sin (dLon / 2) * sin (dLon / 2) * cos (lat1) *
    cos (lat2);
   c = 2 * atan2 (sqrt (a), sqrt (1 - a));
  return earthRadiusKm * c*1000;
}

  //TESTING THE TWO FUNCTIONS//
int main(){
    double y;
    y = distanceCoordinates(30.06422,31.27989,30.06372,31.28013); 
    printf("%lf",y); //y=60.203997

}
