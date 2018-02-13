/*
 *  vec2d.cpp
 *
 *  Created by Lee Grey on 11/06/11.
 *  Copyright 2011 Lee Grey. All rights reserved.
 *
 */

#include "vec2d.h"
#include <iostream>
#include <math.h>

vec2d::vec2d() { 
	x = 0;
	y = 0;
}

vec2d::vec2d( float xInit, float yInit ) { 
	x = xInit;
	y = yInit;
}

void vec2d::set( vec2d& v ) {
	x = v.x;
	y = v.y;
}

void vec2d::set( float xs, float ys ) {
	x = xs;
	y = ys;
}

vec2d vec2d::clone() {
	return vec2d( x, y );
}

void vec2d::zero() {
	x = 0;
	y = 0;	
}

void vec2d::add( vec2d& v ) {
	x += v.x;
	y += v.y;
}

void vec2d::subtract( vec2d& v ) {
	x -= v.x;
	y -= v.y;
}

void vec2d::multiply( float s ) {
	x *= s;
	y *= s;
}

void vec2d::divide( float d ) {
	x /= d;
	y /= d;	
}

void vec2d::normalize() {
	float length = sqrt(x*x+y*y);
    if( length == 0 ) y = 1;
	x /= length;
	y /= length;
}

float vec2d::getLength() {	
   return sqrt(x*x + y*y);
}

void vec2d::setLength( float l ) {
	float length = sqrt( x*x+y*y );
    if( length == 0 ) y = 1;
	x = (x / length) * l;
	y = (y / length) * l;
}

float vec2d::getAngle() {
	return atan2( y, x );
}

float vec2d::getAngleDeg() {
	return atan2(y,x) * 57.2957;
}

void vec2d::setAngle( float a ) {
	float length = sqrt(x*x+y*y);
	x = cos(a)*length;
	y = sin(a)*length;
}

void vec2d::setAngleDeg( float a ) {
	float length = sqrt(x*x+y*y);
	a *= 0.0174532925;
	x = cos(a)*length;
	y = sin(a)*length;
}

void vec2d::rotateBy( float l ) {
	float angle = getAngle();
	float length = sqrt(x*x+y*y);
	x = cos(l+angle)*length;
	y = sin(l+angle)*length;
}

float vec2d::dot( vec2d& v ) {
	return x * v.x + y * v.y;
}

float vec2d::cross( vec2d& v ) {
	return (x * v.y) - (y * v.x);
}

float vec2d::distanceTo( vec2d v ) {
	vec2d distanceVector = vec2d(v.x - x, v.y - y );
	return distanceVector.getLength();
}	

vec2d vec2d::vectorTo( vec2d v ) {
	return vec2d(v.x - x, v.y - y );
}	

void vec2d::lookAt( vec2d& v ) {
	vec2d *vectorToTarget = new vec2d( v.x - x, v.y - y  );
	setAngle( vectorToTarget->getAngle() );
}


void vec2d::reflect( vec2d v ) {
    vec2d unitNormal = v.unit();
    *this = *this - ( unitNormal * ( (unitNormal.dot( *this ) ) * 2 ) );
}

vec2d vec2d::unit() {
    vec2d unit = this->clone();
    unit.normalize();
    return unit;
}

void vec2d::invert() {
    x = -x;
    y = -y; 
}


//OPERATORS

vec2d vec2d::operator+ ( const vec2d& v ) const {
	return vec2d( x + v.x, y + v.y );	
}

vec2d vec2d::operator- ( const vec2d& v ) const {
	return vec2d( x - v.x, y - v.y );	
}

vec2d vec2d::operator* ( const float s ) const {
	return vec2d( x * s, y * s );
}

//dot product
float vec2d::operator* ( const vec2d& v ) const {
    return (x * v.x + y * v.y);
}

//cross product	
float vec2d::operator^ ( const vec2d& v ) const {
	return (x * v.y) - (y * v.x);
}

vec2d vec2d::operator/ ( const float s ) const {
	return vec2d( x / s, y / s );
}

vec2d vec2d::operator/ ( const vec2d& v ) const {
	return vec2d( x / v.x, y / v.y );
}

bool vec2d::operator== ( const vec2d& v ) const {
	return ( x == v.x && y == v.y );
}

void vec2d::operator= ( const vec2d& v ) {
	x = v.x;
	y = v.y;
}

void vec2d::operator+= ( const vec2d& v ) {
	x += v.x;
	y += v.y;	
}

void vec2d::operator-= ( const vec2d& v ) {
	x -= v.x;
	y -= v.y;	
}

void vec2d::operator*= ( const float s ) {
	x *= s;
	y *= s;
}

void vec2d::operator/= ( const float s ) {
	x /= s;
	y /= s;
}

float vec2d::operator[] ( int i ) {
	if ( i == 0 ) return x;
    else return y;
}

void vec2d::print( bool includeEndline ) {
	if( includeEndline ) printf( "%s%f%s%f%s", "[" , x , ",", y , "]\n" );
    else printf( "%s%f%s%f%s", "[" , x , ",", y , "]" );
}

//convenience///////////////

vec2d lgv(float x, float y) {
    return vec2d(x,y);    
}
