#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>
#include <optional>

enum class units : char
{
    k = 10, c, f,
    mph = 20, kmh, ms, kn, fts,
    gal = 30, l, oz,
    lb = 40, kg, g,
    in = 50, ft, yd, mi, km, m, mm,

    err = -1
};

units parseUnits(std::string input)
{
    if (input == "k")   return units::k;   // 10
    if (input == "c")   return units::c;
    if (input == "f")   return units::f;

    if (input == "mph") return units::mph; // 20
    if (input == "kmh") return units::kmh;
    if (input == "ms")  return units::ms;
    if (input == "kn")  return units::kn;
    if (input == "fts") return units::fts;

    if (input == "gal") return units::gal; // 30
    if (input == "l")   return units::l;
    if (input == "oz")  return units::oz;

    if (input == "lb")  return units::lb;  // 40
    if (input == "kg")  return units::kg;
    if (input == "g")   return units::g;

    if (input == "in")  return units::in;  // 50
    if (input == "ft")  return units::ft;
    if (input == "yd")  return units::yd;
    if (input == "mi")  return units::mi;
    if (input == "km")  return units::km;
    if (input == "m")   return units::m;
    if (input == "mm")  return units::mm;

    return units::err;
}

std::optional<float> convert(units a, units b, float val)
{
    int c = static_cast<int>(a),
        d = static_cast<int>(b);


    switch (c * 100 + d)
    {
    case 1011: // k c
        return val - 273.15f;
    case 1012: // k f
        return val * (9.f / 5.f) - 459.67f;
    case 1110: // c k
        return val + 273.15f;
    case 1112: // c f
        return val * (9.f / 5.f) + 32.f;
    case 1210: // f k
        return (val + 459.67f) * (5.0f / 9.0f);
    case 1211: // f c
        return (val - 32.0f) * (5.0f / 9.0f);

    case 2021: // mph kmh
        return val * 1.609344f;
    case 2022: // mph ms
        return val * 0.44704f;
    case 2023: // mph kn
        return val * 0.868976f;
    case 2024: // mph fts
        return val * 1.467f;
    case 2120: // kmh mph
        return val * 0.621371f;
    case 2122: // kmh ms
        return val * 0.277778f;
    case 2123: // kmh kn
        return val * 0.539957f;
    case 2124: // kmh fts
        return val * 0.911344f;
    case 2220: // ms mph
        return val * 2.2369f;
    case 2221: // ms kmh
        return val * 3.6f;
    case 2223: // ms kn
        return val * 1.9438f;
    case 2224: // ms fts
        return val * 3.2808f;
    case 2320: // kn mph
        return val * 1.15078f;
    case 2321: // kn kmh
        return val * 1.852f;
    case 2322: // kn ms
        return val * 0.514444f;
    case 2324: // kn fts
        return val * 1.68781f;
    case 2420: // fts mph
        return val * 0.681818f;
    case 2421: // fts kmh
        return val * 1.09728f;
    case 2422: // fts ms
        return val * 0.3048f;
    case 2423: // fts kn
        return val * 0.592484f;

    case 3031: // gal l
        return val * 3.785411784f;
    case 3032: // gal oz
        return val * 128.0f;
    case 3130: // l gal
        return val * 0.264f;
    case 3132: // l oz
        return val * 33.814022558919f;
    case 3230: // oz gal
        return val / 128.0f;
    case 3231: // oz l
        return val * 0.0295735296875f;

    case 4041: // lb kg
        return val * 0.45359237f;
    case 4042: // lb g
        return val * 453.59237f;
    case 4032: // lb oz
        return val * 16.0f;
    case 4140: // kg lb
        return val * 2.205f;
    case 4142: // kg g
        return val * 1000.0f;
    case 4132: // kg oz
        return val * 35.27396194958f;
    case 4240: // g lb
        return val * 0.0022050f;
    case 4241: // g kg
        return val / 1000.0f;
    case 4232: // g oz
        return val * 0.03527396194958f;
    case 3240: // oz lb
        return val * 0.0625f;
    case 3241: // oz kg
        return val * 0.028349523125f;
    case 3242: // oz g
        return val * 28.349523125f;

    case 5051: // in ft
        return val * (1.0f / 12.0f);
    case 5052: // in yd
        return val * (1.0f / 36.0f);
    case 5053: // in mi
        return val * 0.0000157828282828f;
    case 5054: // in km
        return val * 0.0000254f;
    case 5055: // in m
        return val * 0.0254f;
    case 5056: // in mm
        return val * 25.4f;
    case 5150: // ft in
        return val * 12.0f;
    case 5152: // ft yd
        return val * (1.0f / 3.0f);
    case 5153: // ft mi
        return val * 0.0001893939393939f;
    case 5154: // ft km
        return val / 3280.8f;
    case 5155: // ft m
        return val * 0.3048f;
    case 5156: // ft mm
        return val * 304.8f;
    case 5250: // yd in
        return val * 36.0f;
    case 5251: // yd ft
        return val * 3.0f;
    case 5253: // yd mi
        return val * 0.00056818181f;
    case 5254: // yd km
        return val * 0.0009144f;
    case 5255: // yd m
        return val * 0.9144f;
    case 5256: // yd mm
        return val * 914.4f;
    case 5350: // mi in
        return val * 63360.0f;
    case 5351: // mi ft
        return val * 5280.0f;
    case 5352: // mi yd
        return val * 1760.0f;
    case 5354: // mi km
        return val * 1.609344f;
    case 5355: // mi m
        return val * 1609.344f;
    case 5356: // mi mm
        return val * 1609344.0f;
    case 5450: // km in
        return val * 39370.078740157f;
    case 5451: // km ft
        return val * 3280.839895f;
    case 5452: // km yd
        return val * 1093.6132983f;
    case 5453: // km mi
        return val * 0.62137119f;
    case 5455: // km m
        return val * 1000.0f;
    case 5456: // km mm
        return val * 1000000.0f;
    case 5550: // m in
        return val * 39.370078740157f;
    case 5551: // m ft
        return val * 3.2808f;
    case 5552: // m yd
        return val * 1.0936f;
    case 5553: // m mi
        return val * 0.00062137119f;
    case 5554: // m km
        return val / 1000.0f;
    case 5556: // m mm
        return val * 1000.0f;
    case 5650: // mm in
        return val * 0.039370078740157f;
    case 5651: // mm ft
        return val * 0.0032808f;
    case 5652: // mm yd
        return val * 0.0010936f;
    case 5653: // mm mi
        return val * 0.00000062137119f;
    case 5654: // mm km
        return val / 1000000.0f;
    case 5655: // mm m
        return val / 1000.0f;

    default:
        return {};
    }
}

int main(int argc, char* argv[])
{
    float val;
    
    if (argc == 1)
    {
        std::cout <<
"Ghetto general purpose unit converter application.\n\n\
Units: | Temperature:  | Velocity:          | Volume:              | Mass:         | Lenght:         |\n\
       +–––––––––––––––+––––––––––––––––––––+––––––––––––----------+–––––––––––––––+–––––––––––––––––+\n\
       | <k> Kelvin    | <mph> Miles/h      | <gal> US Gallon      | <lb> Pound    | <in> Inch       |\n\
       | <c> Celsius   | <kmh> Kilometers/h | <l>   Litre          | <kg> Kilogram | <ft> Foot       |\n\
       | <f> Farenheit | <ms>  Meters/s     | <oz>  US Fluid Ounce | <g>  Gram     | <yd> Yard       |\n\
       |               | <kn>  Knots        |                      | <oz> Ounce    | <mi> Mile       |\n\
       |               | <fts> Feet/s       |                      |               | <km> Kilometer  |\n\
       |               |                    |                      |               | <m>  Meter      |\n\
       |               |                    |                      |               | <mm> Millimeter |\n\n\
Syntax: command <from> <to> <value>\n\n\
Example: command c f 34.2    --> converts 34.2C to farenheit\n\
         command mi km 17.5  --> converts 17.5mi to kilometers" << std::endl; 

        return 1;
    }

    std::string from = argv[1];
    std::string to   = argv[2];

    try { val = std::stof(argv[3]); }
        catch(std::exception& e) { return 1; }

    units iFrom = parseUnits(from);
    units iTo   = parseUnits(to);

    if (iFrom == units::err || iTo == units::err) 
        return 1;

    auto con = convert(iFrom, iTo, val);

    if (con.has_value())
        std::cout << con.value() << std::endl;
    else    
        return 1;

    return 0;
}
