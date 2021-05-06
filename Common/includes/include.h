
#ifndef COMMON
#define COMMON

typedef char bool;
typedef char s8;
typedef uchar u8;
typedef int16 s16;
typedef uint16 u16;
typedef int16 s16;
typedef int32 s32;
typedef uint32 u32;
typedef int64 s64;
typedef uint64 u64;
typedef hfloat f16;
typedef float f32;
typedef double f64;

typedef struct
{
    f32 X;
    f32 Y;
} TVector2 <read=TVector2ToString>;

string TVector2ToString( TVector2& value )
{
    local char buffer[255];
    SPrintf( buffer, "[%.6f, %.6f]", value.X, value.Y );

    return buffer;
}

typedef struct
{
    f16 X;
    f16 Y;
} TVector2Half <read=TVector2HalfToString>;

string TVector2HalfToString( TVector2Half& value )
{
    local char buffer[255];
    SPrintf( buffer, "[%.6f, %.6f]", value.X, value.Y );

    return buffer;
}

typedef struct
{
    f32 X;
    f32 Y;
    f32 Z;
} TVector3 <read=TVector3ToString>;

string TVector3ToString( TVector3& value )
{
    local char buffer[255];
    SPrintf( buffer, "[%.6f, %.6f, %.6f]", value.X, value.Y, value.Z );

    return buffer;
}

typedef struct
{
    f16 X;
    f16 Y;
	f16 Z;
} TVector3Half <read=TVector3HalfToString>;

string TVector3HalfToString( TVector3Half& value )
{
    local char buffer[255];
    SPrintf( buffer, "[%.6f, %.6f, %.6f]", value.X, value.Y, value.Z );

    return buffer;
}

typedef struct
{
    f32 X;
    f32 Y;
    f32 Z;
	f32 W;
} TVector4 <read=TVector4ToString>;

string TVector4ToString( TVector4& value )
{
    local char buffer[255];
    SPrintf( buffer, "[%.6f, %.6f, %.6f, %.6f]", value.X, value.Y, value.Z, value.W );

    return buffer;
}

typedef TVector4 TQuaternion;

typedef struct
{
    f16 X;
    f16 Y;
    f16 Z;
	f16 W;
} TVector4Half <read=TVector4HalfToString>;

string TVector4HalfToString( TVector4Half& value )
{
    local char buffer[255];
    SPrintf( buffer, "[%.6f, %.6f, %.6f, %.6f]", value.X, value.Y, value.Z, value.W );

    return buffer;
}

typedef TVector4Half TQuaternionHalf;

typedef struct
{
	TVector3 Min;
	TVector3 Max;
} TExtents3D <read=TExtents3DToString>;

string TExtents3DToString( TExtents3D& value )
{
    local char buffer[255];
    SPrintf( buffer, "[%.6f, %.6f, %.6f] [%.6f, %.6f, %.6f]", value.Min.X, value.Min.Y, value.Min.Z, value.Max.X, value.Max.Y, value.Max.Z );

    return buffer;
}

typedef struct
{
	TVector3 Center;
	f32 Radius;
} TSphere3D <read=TSphere3DToString>;

string TSphere3DToString( TSphere3D& value )
{
    local char buffer[255];
    SPrintf( buffer, "[%.6f, %.6f, %.6f] %.6f]", value.Center.X, value.Center.Y, value.Center.Z, value.Radius );

    return buffer;
}

typedef struct
{
	u32 Value;
} TNormal11_11_11 <read=TNormal11_11_10ToString>;

string TNormal11_11_10ToString( TNormal11_11_11& value )
{
	const int FULL_WIDTH = 32;
	
	const int X_POS = 0;
	const int X_WIDTH = 11;
	const int X_LSHIFT = FULL_WIDTH - X_POS - X_WIDTH;
	const int X_RSHIFT = FULL_WIDTH - X_WIDTH;
	const int X_DOT = (1 << (X_WIDTH - 1)) - 1;
	
	const int Y_POS = X_POS + X_WIDTH;
	const int Y_WIDTH = 11;
	const int Y_LSHIFT = FULL_WIDTH - Y_POS - Y_WIDTH;
	const int Y_RSHIFT = FULL_WIDTH - Y_WIDTH;
	const int Y_DOT = (1 << (Y_WIDTH - 1)) - 1;
	
	const int Z_POS = Y_POS + Y_WIDTH;
	const int Z_WIDTH = 10;	
	const int Z_LSHIFT = FULL_WIDTH - Z_POS - Z_WIDTH;
	const int Z_RSHIFT = FULL_WIDTH - Z_WIDTH;
	const int Z_DOT = (1 << (Z_WIDTH - 1)) - 1;
	
	u32 packed = value.Value;

	int xInt = ((int)(packed << X_LSHIFT)) >> X_RSHIFT;
	int yInt = ((int)(packed << Y_LSHIFT)) >> Y_RSHIFT;
	int zInt = ((int)(packed << Z_LSHIFT)) >> Z_RSHIFT;

	f32 x = (float)xInt / (float)X_DOT;
	f32 y = (float)yInt / (float)Y_DOT;
	f32 z = (float)zInt / (float)Z_DOT;
	
    local char buffer[255];
    SPrintf( buffer, "[%.6f, %.6f, %.6f]", x, y, z );

	return buffer;
}

typedef struct( u32 base )
{
	u32 Offset;
	
	if ( Offset != 0 )
	{
		local u32 returnPos = FTell();
		FSeek( base + Offset );
		string Value;
		FSeek( returnPos );
	}
} TStringOffset <read=TStringOffsetToString>;

string TStringOffsetToString( TStringOffset& value )
{
	if ( value.Offset == 0 ) return "";
    return value.Value;
}

typedef struct
{
    struct
    {
        f32 Column[4];
    } Row[3];
} TMatrix4x3;

typedef struct
{
    struct
    {
        f32 Column[4];
    } Row[4];
} TMatrix4x4;

void PrintValueUInt( string name, u64 value )
{
    PrintValueUIntEx( name, value, true );
}

void PrintValueUIntEx( string name, u64 value, bool newline )
{
    Printf( "%s: %8d (%08X) ", name, value, value );
    if ( newline )
        PrintNl();
}

void PrintValueFloat( string name, u64 value )
{
    PrintValueFloatEx( name, value, true );
}

void PrintValueFloatEx( string name, f32 value, bool newline )
{
    Printf( "%s: %8f ", name, value );
    if ( newline )
        PrintNl();
}

void PrintValueString( string name, string value )
{
    PrintValueStringEx( name, value, true );
}

void PrintValueStringEx( string name, string value, bool newline )
{
    Printf( "%s: %s ", name, value );
    if ( newline )
        PrintNl();
}

void PrintNl()
{
    Printf( "\n" );
}

void PrintArrayUInt( string name, u32 array[], u32 count )
{
    local s32 i;
    local string elementName = "";
    for ( i = 0; i < count; ++i )
    {     
        SPrintf( elementName, "%s[%d]", name, i );
        PrintValueUInt( elementName, array[i] ); 
    }
}

//---------------------------------------------
// Random color
//---------------------------------------------
local u32 __RandomSeed = 0xDEADBABE;
local u32 __RandomBit = 0;
local u32 __RandomCount = 0;
 
u32 MyRandom( u32 to )
{
    ++__RandomCount;
    __RandomBit  = ( (__RandomSeed >> 0 ) ^ ( __RandomSeed >> 2 ) ^ ( __RandomSeed >> 3 ) ^ ( __RandomSeed >> 5 ) ) & 1;
    __RandomSeed = ( ( ( ( __RandomBit << 15 ) | ( __RandomSeed >> 1 ) ) + ( 0xBABE / __RandomCount ) ) % to );

    while( __RandomSeed < 0 )
        __RandomSeed += to;

    return __RandomSeed;
}

local u32 __LastRandomColor = 0;
u32 RandomColor()
{
    return __LastRandomColor = MyRandom( 0xFFFFFFFF );
}

u32 SetRandomBackColor()
{
    local u32 color = RandomColor();
    SetBackColor( color );
    return color;
}

u32 GetShadeOfLastColor(s32 amount)
{    
    local u32 r = (__LastRandomColor & 0x000000FFu) + amount; 
    if (r > 0xFF) r = 0xFF;

    local u32 g = ((__LastRandomColor & 0x0000FF00u) >> 8u) + amount; 
    if (g > 0xFF) g = 0xFF;

    local u32 b = ((__LastRandomColor & 0x00FF0000u) >> 16u) + amount; 
    if (b > 0xFF) b = 0xFF;

    __LastRandomColor = r | g << 8u | b << 16u;  
    return __LastRandomColor;
}

u32 GetLighterShadeOfLastColor()
{
    return GetShadeOfLastColor( 0x10 );
}

u32 SetBackColorToShadeOfLastColor(s32 amount)
{
    local u32 color = GetShadeOfLastColor(amount);
    SetBackColor( color );
    return color;
}

u32 SetBackColorToLighterShadeOfLastColor()
{
    local u32 color = GetShadeOfLastColor(0x10);
    SetBackColor( color );
    return color;
}

u32 StringToInt( char str[] )
{
    local u32 result = 0;
    local u32 length = Strlen( str );

    if ( length > 4 ) length = 4;

    while ( length )
    {
        --length;
        result += str[length] * Pow( 10, length);
    }

    return result;
}

// Generate color uniquely based on a string of 4 or less characters
u32 MyRandomFromString( char str[] )
{
	local u32 to = 0xFFFFFFFF;
	local u32 RandomBit = 0;
	
	if ( Strlen( str ) > 4 ) return MyRandom( to );
	
	local u32 RandomSeed = 0xC0FFEE + StringToInt( str );
	
    RandomBit  = ( (RandomSeed >> 0 ) ^ ( RandomSeed >> 2 ) ^ ( RandomSeed >> 3 ) ^ ( RandomSeed >> 5 ) ) & 1;
    RandomSeed = ( ( ( ( RandomBit << 15 ) | ( RandomSeed >> 1 ) ) + ( 0xBABE ) ) % to );

    while( RandomSeed < 0 )
        RandomSeed += to;

    return RandomSeed;
}

u32 SetRandomBackColorFromString( char str[] )
{
    local u32 color = MyRandomFromString( str );
    SetBackColor( color );
    return color;
}

// Generate u32 from FourCC in string format
u32 ReadFourCC()
{
    local bool isLittle = IsLittleEndian();

    if (isLittle)
        BigEndian();

    local u32 value = ReadUInt();

    if (isLittle)
        LittleEndian();

    return value;
}

u32 FourCC( string str )
{
    return (u32)str[0] << 24 | (u32)str[1] << 16 | (u32)str[2] << 8 | (u32)str[3];
}

u32 MakeFourCC( string str )
{
    if ( IsLittleEndian() )
        return (u32)str[0] | (u32)str[1] << 8 | (u32)str[2] << 16 | (u32)str[3] << 24;
    else
        return (u32)str[3] | (u32)str[2] << 8 | (u32)str[1] << 16 | (u32)str[0] << 24;
}

u32 Align( u32 value, u32 alignment )
{
	return (value + (alignment - 1)) & ~(alignment - 1);
}

void FAlign( u32 alignment )
{
	FSeek( Align( FTell(), alignment ) );
}

local u64 gBasePositionStack[32];
local u32 gBasePositionStackIndex = 0;
local u64 gBasePosition = 0;

local u64 gPositionStack[32];
local u32 gPositionStackIndex = 0;

void FPushBase()
{
    gBasePosition = gBasePositionStack[ ++gBasePositionStackIndex ] = FTell();
    //PrintValueUInt( "Push: gBasePosition", gBasePosition ); 
}

void FPopBase()
{
    gBasePosition = gBasePositionStack[ --gBasePositionStackIndex ];
    //PrintValueUInt( "Pop: gBasePosition", gBasePosition ); 
}

void FPush()
{
    gPositionStack[ ++gPositionStackIndex ] = FTell();
}

void FPushRel( u64 pos )
{
    gPositionStack[ ++gPositionStackIndex ] = FTell();
    FSeekRel( pos );
}

void FPushAbs( u64 pos )
{
    gPositionStack[ ++gPositionStackIndex ] = FTell();
    FSeek( pos );
}

void FPop()
{
    FSeek( gPositionStack[ gPositionStackIndex-- ] );
}

void FSeekRel( u64 pos )
{
    FSeek( gBasePosition + pos );
}

s32 ArrayIndexOfUInt( u32 array[], u32 count, u32 value )
{
    local s32 i;
    for ( i = 0; i < count; ++i )
        if ( array[i] == value )
            return i;

    return -1;
}

bool ArrayContainsUInt( u32 array[], u32 count, u32 value )
{
    return ArrayIndexOfUInt( array, count, value ) != -1;
}

void ArrayFillUInt( u32 array[], u32 count, u32 value )
{
    local u32 i;
    for ( i = 0; i < count; ++i )
        array[i] = value;
}

void ArrayMinUInt( u32 array[], u32 count )
{
    local u32 i;
    local u32 min = 0xFFFFFFFF;

    for ( i = 0; i < count; ++i )
    {
        if ( array[i] < min ) 
            min = array[i];
    }

    return max;
}

void ArrayMaxUInt( u32 array[], u32 count )
{
    local u32 i;
    local u32 max = 0;

    for ( i = 0; i < count; ++i )
    {
        if ( array[i] > max ) 
            max = array[i];
    }

    return max;
}

#endif // #ifndef COMMON
