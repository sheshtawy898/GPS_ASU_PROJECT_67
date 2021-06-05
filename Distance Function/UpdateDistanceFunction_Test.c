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
   //FUNCTION TO ACCUMULATE DISTANCE//
double UpdateDistance (double lat1 , double lon1 , double lat2, double lon2 , double distance){

    if (lat1 != 0 && lon1 != 0)
    {
        distance += distanceCoordinates (lat1, lon1, lat2, lon2);
    }
    lat1 = lat2;
    lon1 = lon2;
}
  //TESTING FUNCTIONS//
int main()
{
    double distance =0;

    double lat1=0 ,lat2=30.06421 , lon1=0 , lon2=31.27842;
    distance += UpdateDistance( lat1 , lon1 , lat2, lon2, distance );
    printf("%lf\n" , distance);

    lat2=30.06429 ,lat1=30.06421 , lon2=31.27864 , lon1=31.27842;
    distance += UpdateDistance( lat1 , lon1 , lat2, lon2, distance );
    printf("%lf" , distance);
}
