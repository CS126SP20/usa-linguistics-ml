//
// Created by hrishi on 4/30/20.
//

#include <mylibrary/organizer.h>
#include <mylibrary/response.h>

#include <fstream>
#include <iostream>

namespace mylibrary {
// Use every 6 lines of the trainingresponses file to create response
std::vector<std::vector<std::string>> Organizer::CreateRawResponse(
    const std::string &file) {
  // Create a new file stream
  std::ifstream file_stream;
  file_stream.open(file);
  std::vector<std::vector<std::string>> training_responses;

  if (file_stream.is_open()) {
    int line_counter = 0;
    std::string line;
    std::vector<std::string> response_as_string;

    // Takes in each line from trainingimages file
    while(getline(file_stream, line)) {
      response_as_string.push_back(line);
      line_counter++;

      if (line_counter == kResponseLength) {
        training_responses.push_back(response_as_string);
        response_as_string.clear(); // Reset the image
        line_counter = 0;
      }
    }
    file_stream.close();
  } else {
    std::cerr << "Your file couldn't be opened or doesn't exist." << std::endl;
  }

  return training_responses;
}

// Returns a vector<int> corresponding to the region they are from
std::vector<int> Organizer::CreateAnswer(const std::string &file) {
  // Create a brand new file stream
  std::ifstream file_stream;
  file_stream.open(file);
  std::vector<int> training_answer;

  if (file_stream.is_open()) {
    std::string line;
    // Takes in each line from traininganswers file
    while(getline(file_stream, line)) {
      training_answer.push_back(std::stoi(line));
    }
    file_stream.close();
  } else {
    std::cerr << "Your file couldn't be opened or doesn't exist." << std::endl;
  }

  // Return geographical regions as a vector of ints
  return training_answer;
}

// Combines string responses and their corresponding answer (region) to form
// a vector of true responses
std::vector<Response> Organizer::CreateRealResponse(const std::vector<std::vector<std::string>>
                                          &training_responses, std::vector<int> training_answers) {
  std::vector<Response> responses;
  int counter = 0;

  for (const std::vector<std::string> &response_as_string : training_responses) {
    try {
      Response new_response = Response(response_as_string, training_answers.at(counter));
      responses.push_back(new_response);
      counter++;
    }
    catch (const std::out_of_range &exception){
      std::cout << "Out of range exception: " << exception.what() << std::endl;
    }
  }

  real_responses = responses;
  return responses;
}

}  // namespace mylibrary