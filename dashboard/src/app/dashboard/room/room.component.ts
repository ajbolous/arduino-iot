import { Component, OnInit, Input, ViewChild } from '@angular/core';
import { BaseChartDirective, Label } from 'ng2-charts';
import { ChartDataSets, ChartOptions } from 'chart.js';
import { AngularFireDatabase } from '@angular/fire/database';

@Component({
  selector: 'app-room',
  templateUrl: './room.component.html',
  styleUrls: ['./room.component.css']
})
export class RoomComponent implements OnInit {

  @Input() roomId: string;
  public databasePath: string;
  public lastTimestamp = 0;
  public lastTemperature = 0;
  public lastHumidity = 0;

  chartOptions: ChartOptions = {
    maintainAspectRatio: false,
    legend: {
      display: false
    },
    scales: {
      xAxes: [{ gridLines: { display: false }, ticks: { display: false}}],
      yAxes: [{ gridLines: { display: false }, id: 'T', ticks: { stepSize: 2 }, }, { id: 'H', gridLines: { display: false }, ticks: { stepSize: 2 } }]
    }
  };
  chartLabels: Label[] = [];
  chartData: ChartDataSets[] = [
    { data: [], label: 'Temperature', yAxisID: 'T' },
    { data: [], label: 'Humidity', yAxisID: 'H' },
  ];

  @ViewChild(BaseChartDirective, { static: true }) chart: BaseChartDirective;

  constructor(public db: AngularFireDatabase) { }

  ngOnInit() {
    this.databasePath = '/data/' + this.roomId;
    this.db.list(this.databasePath, ref => ref.limitToLast(12 * 60))
      .valueChanges()
      .subscribe((measures: { temperature: number, humidity: number }[]) => {
        const humidity = [];
        const temps = [];
        const labels = [];
        let index = measures.length;
        for (const temp of measures) {
          index--;
          const d = new Date(Date.now() - index * 60000);
          d.setSeconds(0);
          labels.push(d.toLocaleString());
          temps.push(temp.temperature);
          humidity.push(temp.humidity);
        }
        this.lastTemperature = measures[measures.length - 1].temperature;
        this.lastHumidity = measures[measures.length - 1].humidity;
        this.chartLabels = labels;
        this.chartData[0].data = temps;
        this.chartData[1].data = humidity;
      });

    this.db.object('/nodes/' + this.roomId).valueChanges().subscribe((timestamp: number) => {
      this.lastTimestamp = timestamp;
    });
  }

  alive() {
    return this.lastTimestamp && (Date.now() - this.lastTimestamp) < 5 * 60 * 1000;
  }


}