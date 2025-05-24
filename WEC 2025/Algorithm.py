from math import cos, asin, sqrt, pi

def distance(lat1, lon1, lat2, lon2):
    r = 2.5 # radius of circle in km
    rads = pi / 180

    a = 0.5 - cos((lat2-lat1)*rads)/2 + cos(lat1*rads) * cos(lat2*rads) * (1-cos((lon2-lon1)*rads))/2
    return 2 * r * asin(sqrt(a))

main(void){
    print(distance())
}