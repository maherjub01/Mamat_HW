#include "string.h"
#include <iostream>
#include <cstring>

// initializes empty string
String :: String(){

	this->length = 1;
	this->data = new char[1];
	this->data[0] = '\0';
}

// initialize a string from another string
String :: String(const String &str){

	this->length = str.length;
	this->data = new char[length];
	strcpy(this->data, str.data);
}

// clone
String :: String(const char *str){

	this->length = strlen(str) + 1;
	this->data = new char[length];
	strcpy(this->data, str);
}

// destruct
String :: ~String(){

	delete[] this->data;
}

String &String :: operator=(const String &rhs){

	delete[] this->data;
	this->length = rhs.length;
	this->data = new char[this->length];
	strcpy(this->data, rhs.data);
	return *this;
}

String &String :: operator=(const char *str){

	delete[] this->data;
	this->length = strlen(str)+1;
	this->data = new char[this->length];
	strcpy(this->data, str);
	return *this;
}

bool String :: equals(const String &rhs) const{

	if (rhs.length != this->length){

		return false;
	}

	if (!strcmp(rhs.data, this->data)){
	
		return true;
	}

	return false;
}

bool String :: equals(const char *rhs) const{

	if ((strlen(rhs)+1) != this->length){

		return false;
	}

	if (!strcmp(rhs, this->data)){
	
		return true;
	}

	return false;
}

void String::split(const char *delimiters, String **output,
                                           size_t *size) const{

    if (delimiters == NULL || size == 0){
        return;
    }
    size_t sub_str_arr_len = 1;
    int index = 0;
    char target_arr[strlen(delimiters)+1];
    strcpy(target_arr,delimiters);
    if(this->data == NULL){
        *size = 0;
        *output = NULL;
        return;
    }
    char throwaway_str[length + 1];
    strcpy(throwaway_str,data);
    for(int j = 0; throwaway_str[j]!='\0'; j++){
        for(int i = 0; target_arr[i]!='\0'; i++){
            if (target_arr[i] == throwaway_str[j]){
                sub_str_arr_len +=1;
            }
        }
    }
    if (output == NULL){
        *size = sub_str_arr_len;
        return;
    }
    *output = new String[sub_str_arr_len];
    *size = sub_str_arr_len;
    int left_idx = 0;
    for(int i = 0; throwaway_str[i]!='\0'; i++){
        for(int j = 0; target_arr[j]!='\0'; j++){
            if (target_arr[j] == throwaway_str[i]){
                if (left_idx != i){
                    throwaway_str[i] = '\0';
                    (*output)[index] =String(&throwaway_str[left_idx]);
                }

                else{
                    (*output)[index] =NULL;
                }

                left_idx = i+1;
                index++;
            }
        }
    }
    for(int i = 0; target_arr[i]!='\0'; i++){
        if(throwaway_str[length-1] == target_arr[i]){
            (*output)[index] =NULL;
        }
        else{
            (*output)[index] =String(&throwaway_str[left_idx]);
        }
    }
    return;
}



int String::to_integer() const{

	return atoi(this->data);
}
            
String String::trim() const{

    char copied_string[length+1];
    int leading_index = 0;
    int trailing_index = (int)length - 1;
    strcpy(copied_string,data);

    while (copied_string[leading_index] == ' ') {
        leading_index++;
    }

    while (copied_string[trailing_index] == ' ') {
        trailing_index--;
    }

    int len_after_trim = trailing_index-leading_index+1;
    char* clean_string = new char[len_after_trim+1]();

    int i = 0;
    while (leading_index <= trailing_index){
        clean_string[i] = data[leading_index];
        leading_index++;
        i++;
    }

    clean_string[len_after_trim] = '\0';
    String cleaned = String(clean_string);

    delete[](clean_string);

    return cleaned;
}
