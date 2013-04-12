struct vector3d
{
    float X, Y, Z;
 
    inline vector3d( void ) {}
    inline vector3d( const float x, const float y, const float z )
    { X = x; Y = y; Z = z; }

    inline vector3d operator + ( const vector3d& A ) const
    { return vector3d( X + A.X, Y + A.Y, Z + A.Z ); }

    inline vector3d operator + ( const float A ) const
    { return vector3d( X + A, Y + A, Z + A ); }

    inline float Dot( const vector3d& A ) const
    { return A.X*X + A.Y*Y + A.Z*Z; }
};

struct triangle
{
	vector3d A, B, C;

	inline triangle( void ) {}
    inline triangle( const vector3d a, const vector3d b, const vector3d c)
    { A = a; B = b; C = c;}
};

struct quad
{
	vector3d A, B, C, D;

	inline quad( void ) {}
    inline quad( const vector3d a, const vector3d b, const vector3d c, const vector3d d)
    { A = a; B = b; C = c; D = d;}
};