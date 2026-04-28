package com.github.Artem_Pb.repository;

import com.github.Artem_Pb.domain.SimpleTask;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;

import java.util.List;

public interface SimpleTaskRepository extends JpaRepository<SimpleTask, Long> {
    @Query("SELECT s FROM SimpleTask s WHERE s.id NOT IN " +
            "(SELECT st.id FROM MegaTask m JOIN m.subTasks st)")
    List<SimpleTask> findAllTopLevel();
    @Query("SELECT s FROM SimpleTask s WHERE s.id NOT IN " +
            "(SELECT st.id FROM MegaTask m JOIN m.subTasks st) " +
            "AND LOWER(s.title) LIKE LOWER(CONCAT('%', :keyword, '%'))")
    List<SimpleTask> findTopLevelByTitleContaining(@Param("keyword") String keyword);
}
