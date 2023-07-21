#pragma once

#include <math.h>
#include <stdio.h>


class KalmanFilter {
  public:

  // State vector
  struct state {
    double x;
    double y;
    double z;
    double vx;
    double vy;
    double vz;
  };

  // Measurement vector
  struct measurement {
    double x;
    double y;
    double z;
  };

  // Process model
  struct process_model {
    double dt;
    double ax;
    double ay;
    double az;
  };

  // Measurement model
  struct measurement_model {
    double R;
  };

  // Kalman filter
  struct kalman_filter {
    struct state state;
    struct process_model process_model;
    struct measurement_model measurement_model;
    double P;
    double Q;
    double R;
  };

  // Initialize Kalman filter
  void init(struct kalman_filter *filter, double dt, double ax, double ay, double az, double R) {
    filter->state.x = 0.0;
    filter->state.y = 0.0;
    filter->state.z = 0.0;
    filter->state.vx = 0.0;
    filter->state.vy = 0.0;
    filter->state.vz = 0.0;
    filter->process_model.dt = dt;
    filter->process_model.ax = ax;
    filter->process_model.ay = ay;
    filter->process_model.az = az;
    filter->measurement_model.R = R;
    filter->P = 1.0;
    filter->Q = 0.01;
  }

  // Predict state
  void predict(struct kalman_filter *filter) {
    // Calculate the predicted state
    filter->state.x += filter->state.vx * filter->process_model.dt;
    filter->state.y += filter->state.vy * filter->process_model.dt;
    filter->state.z += filter->state.vz * filter->process_model.dt;
    filter->state.vx += filter->process_model.ax * filter->process_model.dt;
    filter->state.vy += filter->process_model.ay * filter->process_model.dt;
    filter->state.vz += filter->process_model.az * filter->process_model.dt;

    // Calculate the predicted covariance
    filter->P = filter->P + filter->Q;
  }

  // Update state with measurement
  void update(struct kalman_filter *filter, struct measurement measurement) {
    // Calculate the Kalman gain
    double K = filter->P * filter->measurement_model.R / (filter->P * filter->measurement_model.R + filter->Q);

    // Update the state
    filter->state.x += K * (measurement.x - filter->state.x);
    filter->state.y += K * (measurement.y - filter->state.y);
    filter->state.z += K * (measurement.z - filter->state.z);

    // Update the covariance
    filter->P = (1.0 - K) * filter->P;
  }

  // Run Kalman filter
  void run(struct kalman_filter *filter, struct measurement measurement) {
    predict(filter);
    update(filter, measurement);
  }

protected:

};