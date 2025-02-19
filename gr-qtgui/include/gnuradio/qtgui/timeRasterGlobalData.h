/* -*- c++ -*- */
/*
 * Copyright 2012,2013 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef TIMERASTER_GLOBAL_DATA_HPP
#define TIMERASTER_GLOBAL_DATA_HPP

#include <qwt_raster_data.h>
#include <cinttypes>

#if QWT_VERSION >= 0x060000
#include <qwt_interval.h>

typedef QwtInterval QwtDoubleInterval;
#endif

class TimeRasterData : public QwtRasterData
{
public:
    TimeRasterData(const double rows, const double cols);
    ~TimeRasterData() override;

    virtual void reset();
    virtual void copy(const TimeRasterData*);

    virtual void resizeData(const double rows, const double cols);

    virtual QwtRasterData* copy() const;

#if QWT_VERSION < 0x060000
    virtual QwtDoubleInterval range() const;
    virtual void setRange(const QwtDoubleInterval&);
#elif QWT_VERSION >= 0x060200
    virtual QwtInterval interval(Qt::Axis) const override;
    void setInterval(Qt::Axis, const QwtInterval&);
#endif

    double value(double x, double y) const override;

    virtual double getNumCols() const;
    virtual double getNumRows() const;

    virtual void addData(const double*, const int);

    void incrementResidual();

protected:
    std::vector<double> d_data;
    double d_rows, d_cols;
    double d_resid;
    int d_nitems, d_totalitems;

#if QWT_VERSION < 0x060000
    QwtDoubleInterval d_intensityRange;
#else
    QwtInterval d_intensityRange;
#endif

#if QWT_VERSION >= 0x060200
    QwtInterval d_intervals[3];
#endif

private:
};

#endif /* TIMERASTER_GLOBAL_DATA_HPP */
