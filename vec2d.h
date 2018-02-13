/*
 *  Vector2D.h
 *
 *  Created by Lee Grey on 11/06/11.
 *  Copyright 2011 Lee Grey. All rights reserved.
 *
 */

#ifndef _vec2d_
#define _vec2d_

class vec2d {
    
	public :
    
	float x, y;
	vec2d();
	vec2d( float xInit, float yInit );
    
	void zero();
	void set( vec2d& v );
	void set( float xs, float ys );
	vec2d clone();
    
	void setAngle( float a );
	void setAngleDeg( float a );	
	float getAngle();
	float getAngleDeg();
	void rotateBy( float l );	
    
	void add( vec2d& v );
	void subtract( vec2d& v );
	void multiply( float s );
	void divide( float s );
    
	void normalize();
	void setLength( float l );
	float getLength();
    
	float dot( vec2d& v );
	float cross( vec2d& v );
	float distanceTo( vec2d v );
	vec2d vectorTo( vec2d v );	
	void lookAt( vec2d& v );
    void reflect( vec2d v );
    vec2d unit();
    void invert();
    
	void print( bool includeEndline = true );
    
	vec2d operator+ ( const vec2d& v ) const;
	vec2d operator- ( const vec2d& v ) const;
	vec2d operator* ( const float s ) const;	
	float operator* ( const vec2d& v ) const; //dot product
	float operator^ ( const vec2d& v ) const; //cross product	
	vec2d operator/ ( const float s ) const;
	vec2d operator/ ( const vec2d& v ) const;
	bool operator== ( const vec2d& v ) const;
	void operator= ( const vec2d& v );
	void operator+= ( const vec2d& v );
	void operator-= ( const vec2d& v );
	void operator*= ( const float s );	
	void operator/= ( const float s );
	float operator[] ( int i );
    
};

vec2d lgv(float x, float y);

#endif