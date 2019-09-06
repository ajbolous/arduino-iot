import { Component, OnInit, ViewChild } from '@angular/core';
import { AngularFireDatabase } from '@angular/fire/database';
import { map } from 'rxjs/operators';

@Component({
  selector: 'app-dashboard',
  templateUrl: './dashboard.component.html',
  styleUrls: ['./dashboard.component.css']
})
export class DashboardComponent implements OnInit {

  public nodes: string[] = [];
  public numberOfCols = 1;

  constructor(public db: AngularFireDatabase) { }

  onResize(event) {
    this.numberOfCols = (window.innerWidth <= 800) ? 1 : 2;
  }

  ngOnInit() {
    this.onResize({});
    this.db.list('/nodes').snapshotChanges().pipe(map(changes => {
      return changes.map(c => ({ key: c.payload.key, val: c.payload.val() }));
    })).subscribe(items => {
      console.log(items);
      this.nodes = [];
      items.forEach(item => this.nodes.push(item.key));
    });
  }
}
