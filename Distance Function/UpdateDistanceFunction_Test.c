#include <stdio.h>
#include<math.h>
double lat1 =0 , lon1=0 , lat2=0 , lon2=0 ;
double DISTANCE=0;
double dist_2p;
    //GETTING LAT AND LON AFTER CONNECTING GPS//
 /*double latFromGPS{}
   double lonFromGPS{} */

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


int main(){

printf("Enter Lat2 then lon2:\n" );  //to try to get the coordinates as if the gps module is connected
scanf("%lf", &lat2);
scanf("%lf", &lon2);
 dist_2p= distanceCoordinates(lat1, lon1 ,lat2, lon2);

 //while loop to exit when the distance exceeds 100 meters
while (DISTANCE < 100){
    lat1=lat2;
    lon1=lon2;
    printf("Enter Lat2 then lon2:\n" );
    scanf("%lf", &lat2);
    scanf("%lf", &lon2);
    dist_2p= distanceCoordinates(lat1, lon1 ,lat2, lon2);
    DISTANCE += dist_2p;
}

printf("%lf", DISTANCE); //final distance


}
